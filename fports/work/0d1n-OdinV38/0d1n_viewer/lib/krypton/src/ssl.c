/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

#include "ktypes.h"

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

int SSL_library_init(void) {
  return 1;
}

SSL *SSL_new(SSL_CTX *ctx) {
  SSL *ssl;

  ssl = calloc(1, sizeof(*ssl));
  if (NULL == ssl) goto out;

  assert(ctx != NULL);

  ssl->ctx = ctx;
  ssl->fd = -1;

  /* success */
  goto out;

#if 0
out_free:
  free(ssl);
  ssl = NULL;
#endif
out:
  return ssl;
}

int SSL_set_fd(SSL *ssl, int fd) {
  ssl->fd = fd;
  ssl_err(ssl, SSL_ERROR_NONE);
  return 1;
}

int SSL_get_fd(SSL *ssl) {
  return ssl->fd;
}

int SSL_set_cipher_list(SSL *ssl, const char *str) {
  /* TODO(rojer): Implement this. */
  (void) str;
  ssl_err(ssl, SSL_ERROR_SSL);
  return 0;
}

static int do_send(SSL *ssl) {
  const uint8_t *buf;
  size_t len, send_len;
  ssize_t ret;

  buf = ssl->tx_buf;
  len = ssl->tx_len;

  if (!len) {
    ssl->write_pending = 0;
    return 1;
  }
again:

#if KRYPTON_DEBUG_NONBLOCKING
  send_len = 1;
#else
  send_len = len;
#endif
  ret = kr_send(ssl->fd, buf, send_len, MSG_NOSIGNAL);
  dprintf(
      ("kr_send(%d, %p, %d) = %d\n", ssl->fd, buf, (int) send_len, (int) ret));
  if (ret < 0) {
    if (SOCKET_ERRNO == EWOULDBLOCK) {
      goto shuffle;
    }
    ssl_err(ssl, SSL_ERROR_SYSCALL);
    ssl->tx_len = 0;
    ssl->write_pending = 0;
    return 0;
  }
  if (ret == 0) {
    dprintf(("send: peer hung up\n"));
    ssl_err(ssl, SSL_ERROR_ZERO_RETURN);
    ssl->tx_len = 0;
    ssl->write_pending = 0;
    return 0;
  }

  if ((size_t) ret >= len) {
    ssl->tx_len = 0;
    ssl->write_pending = 0;
    return 1;
  }

  buf += ret;
  len -= ret;

#if KRYPTON_DEBUG_NONBLOCKING
  if (len) {
    goto shuffle;
  }
#endif

  goto again;
shuffle:
  ssl->tx_len = len;
  memmove(ssl->tx_buf, buf, ssl->tx_len);
  ssl_err(ssl, SSL_ERROR_WANT_WRITE);
  if (ssl->tx_len == 0) {
    /* Keep idle memory consumption low. */
    free(ssl->tx_buf);
    ssl->tx_max_len = 0;
  }
  return 0;
}

static int do_recv(SSL *ssl, uint8_t *out, size_t out_len) {
  uint8_t *ptr;
  ssize_t ret;
  size_t len;

  dprintf(("do_recv %d %d\n", (int) ssl->rx_len, (int) ssl->rx_max_len));
  if (NULL == ssl->rx_buf) {
    ssl->rx_buf = malloc(RX_INITIAL_BUF);
    if (NULL == ssl->rx_buf) {
      ssl_err(ssl, SSL_ERROR_SYSCALL);
      return 0;
    }

    ssl->rx_max_len = RX_INITIAL_BUF;
    ssl->rx_len = 0;
  }
  if (ssl->rx_len >= ssl->rx_max_len) {
    uint8_t *new;
    size_t new_len;

    /* FIXME: peek for size */
    new_len = ssl->rx_max_len + RX_INITIAL_BUF;
    new = realloc(ssl->rx_buf, new_len);
    if (NULL == new) {
      ssl_err(ssl, SSL_ERROR_SYSCALL);
      return 0;
    }

    ssl->rx_buf = new;
    ssl->rx_max_len = new_len;
  }

  ptr = ssl->rx_buf + ssl->rx_len;
#if KRYPTON_DEBUG_NONBLOCKING
  len = 1;
#else
  len = ssl->rx_max_len - ssl->rx_len;
#endif

  ret = kr_recv(ssl->fd, ptr, len, MSG_NOSIGNAL);
  dprintf(("kr_recv(%d, %p, %d): %d %d\n", ssl->fd, ptr, (int) len, (int) ret,
           errno));
  if (ret < 0) {
    if (SOCKET_ERRNO == EWOULDBLOCK) {
      ssl_err(ssl, SSL_ERROR_WANT_READ);
      return 0;
    }
    dprintf(("recv: %s\n", strerror(errno)));
    ssl_err(ssl, SSL_ERROR_SYSCALL);
    return 0;
  }

  if (ret == 0) {
    ssl_err(ssl, SSL_ERROR_ZERO_RETURN);
    dprintf(("peer hung up\n"));
    return 0;
  }

  ssl->rx_len += ret;

  if (!tls_handle_recv(ssl, out, out_len)) {
    ssl_err(ssl, SSL_ERROR_SSL);
    return 0;
  }

  /* In case any alerts are queued */
  if (!do_send(ssl)) return 0;

#if KRYPTON_DEBUG_NONBLOCKING
  if (ssl->rx_len) {
    ssl_err(ssl, SSL_ERROR_WANT_READ);
    return 0;
  }
#endif

  return 1;
}

int SSL_accept(SSL *ssl) {
  if (ssl->fatal) {
    ssl_err(ssl, SSL_ERROR_SSL);
    return -1;
  }
  if (ssl->close_notify || ssl->state == STATE_CLOSING) {
    ssl_err(ssl, SSL_ERROR_ZERO_RETURN);
    return 0;
  }

  if (ssl->mode_defined && !ssl->is_server) {
    dprintf(("bad mode in accept\n"));
    ssl_err(ssl, SSL_ERROR_SSL);
    return 0;
  }

  while (ssl->tx_len) {
    if (!do_send(ssl)) return -1;
  }

  switch (ssl->state) {
    case STATE_INITIAL:
      ssl->is_server = 1;
      ssl->mode_defined = 1;
      kr_set_state(ssl, STATE_CL_HELLO_WAIT);

    /* fall through */
    case STATE_CL_HELLO_WAIT:
      while (ssl->state != STATE_CL_HELLO_RCVD) {
        if (!do_recv(ssl, NULL, 0)) {
          return -1;
        }
      }

    /* fall through */
    case STATE_CL_HELLO_RCVD:
      if (!tls_sv_hello(ssl)) {
        return 0;
      }

      kr_set_state(ssl, STATE_SV_HELLO_SENT);
      if (!do_send(ssl)) return -1;

    /* fall through */
    case STATE_SV_HELLO_SENT:
      while (ssl->state != STATE_CLIENT_FINISHED) {
        if (!do_recv(ssl, NULL, 0)) {
          return -1;
        }
      }

    /* fall through */
    case STATE_CLIENT_FINISHED:
      if (!tls_sv_finish(ssl)) {
        return 0;
      }

      kr_set_state(ssl, STATE_ESTABLISHED);
      if (!do_send(ssl)) return -1;

    /* fall through */
    default:
      break;
  }

  ssl_err(ssl, SSL_ERROR_NONE);
  return 1;
}

int SSL_connect(SSL *ssl) {
  tls_sec_t sec;

  if (ssl->fatal) {
    ssl_err(ssl, SSL_ERROR_SSL);
    return -1;
  }
  if (ssl->close_notify || ssl->state == STATE_CLOSING) {
    ssl_err(ssl, SSL_ERROR_ZERO_RETURN);
    return 0;
  }

  if (ssl->mode_defined && ssl->is_server) {
    dprintf(("bad mode in connect\n"));
    ssl_err(ssl, SSL_ERROR_SSL);
    return 0;
  }

  while (ssl->tx_len) {
    if (!do_send(ssl)) return -1;
  }

  switch (ssl->state) {
    case STATE_INITIAL:
      ssl->is_server = 0;
      ssl->mode_defined = 1;

      sec = tls_new_security();
      if (NULL == sec) {
        ssl_err(ssl, SSL_ERROR_SYSCALL);
        return -1;
      }
      ssl->nxt = sec;

      if (!tls_cl_hello(ssl)) {
        dprintf(("failed to construct hello\n"));
        ssl_err(ssl, SSL_ERROR_SYSCALL);
        return -1;
      }

      kr_set_state(ssl, STATE_CL_HELLO_SENT);
      if (!do_send(ssl)) return -1;

    /* fall through */

    case STATE_CL_HELLO_SENT:
    case STATE_SV_HELLO_RCVD:
    case STATE_SV_CERT_RCVD:
      while (ssl->state != STATE_SV_DONE_RCVD) {
        if (!do_recv(ssl, NULL, 0)) {
          return -1;
        }
      }

    /* fall through */
    case STATE_SV_DONE_RCVD:
      if (ssl->cert_requested) {
        const PEM *cert = ssl->ctx->pem_cert;
        PEM empty;
        if (ssl->ctx->pem_cert == NULL) {
          dprintf(("warning: client cert requested but none is provided\n"));
          /* We still need to send an empty message. */
          memset(&empty, 0, sizeof(empty));
          cert = &empty;
        }
        if (!tls_send_certs(ssl, cert)) {
          dprintf(("failed to send client certs\n"));
          ssl_err(ssl, SSL_ERROR_SYSCALL);
          return -1;
        }
      }
      if (!tls_cl_finish(ssl)) {
        dprintf(("failed to construct key exchange\n"));
        ssl_err(ssl, SSL_ERROR_SYSCALL);
        return -1;
      }

      kr_set_state(ssl, STATE_CLIENT_FINISHED);
      if (!do_send(ssl)) return -1;

    /* fall through */
    case STATE_CLIENT_FINISHED:
      while (ssl->state != STATE_ESTABLISHED) {
        if (!do_recv(ssl, NULL, 0)) {
          return -1;
        }
      }

    default:
      break;
  }

  ssl_err(ssl, SSL_ERROR_NONE);
  return 1;
}

int SSL_read(SSL *ssl, void *buf, int num) {
  if (ssl->fatal) {
    ssl_err(ssl, SSL_ERROR_SSL);
    return -1;
  }

  if (ssl->extra_appdata.len > 0) {
    int rlen = min(num, (int) ssl->extra_appdata.len);
    dprintf(("yielding %d extra bytes\n", rlen));
    memcpy(buf, ssl->extra_appdata.ptr, rlen);
    ssl->extra_appdata.len -= rlen;
    ssl->extra_appdata.ptr += rlen;
    if (ssl->extra_appdata.len == 0) {
      size_t shift_len = (ssl->appdata_eom - ssl->rx_buf);
      ssl->rx_len -= shift_len;
      dprintf(("extra data consumed, shift %d, %d left\n", (int) shift_len,
               (int) ssl->rx_len));
      if (ssl->rx_len > 0) {
        memmove(ssl->rx_buf, ssl->rx_buf + shift_len, ssl->rx_len);
      } else {
        /* Keep idle memory consumption low. */
        free(ssl->rx_buf);
        ssl->rx_buf = NULL;
        ssl->rx_max_len = ssl->rx_len = 0;
      }
    }
    return rlen;
  }

  if (ssl->close_notify || ssl->state == STATE_CLOSING) {
    ssl_err(ssl, SSL_ERROR_ZERO_RETURN);
    return 0;
  }

  ssl->copied = 0;
  ssl->got_appdata = 0;

  if (ssl->rx_len > 0) {
    /* Try decoding what is in the buffer already. */
    if (!tls_handle_recv(ssl, buf, num)) {
      ssl_err(ssl, SSL_ERROR_SSL);
      return 0;
    }
  }

  while (!ssl->got_appdata) {
    if (ssl->state != STATE_ESTABLISHED) {
      int ret;
      if (ssl->is_server) {
        ret = SSL_accept(ssl);
      } else {
        ret = SSL_connect(ssl);
      }
      if (ret <= 0) return ret;
    }

    if (!do_recv(ssl, buf, num)) {
      return ssl->err == SSL_ERROR_ZERO_RETURN ? 0 : -1;
    }
  }

  ssl_err(ssl, SSL_ERROR_NONE);
  return ssl->copied;
}

int SSL_write(SSL *ssl, const void *buf, int num) {
  int res = num;
  if (num == 0 && ssl->tx_len > 0) {
    if (!do_send(ssl)) return -1;
    ssl_err(ssl, ssl->fatal ? SSL_ERROR_SSL : SSL_ERROR_NONE);
    return 0;
  }
  if (ssl->fatal) {
    ssl_err(ssl, SSL_ERROR_SSL);
    return -1;
  }
  if (ssl->close_notify || ssl->state == STATE_CLOSING) {
    ssl_err(ssl, SSL_ERROR_ZERO_RETURN);
    return 0;
  }

  if (ssl->state != STATE_ESTABLISHED) {
    int ret;
    if (ssl->is_server) {
      ret = SSL_accept(ssl);
    } else {
      ret = SSL_connect(ssl);
    }
    if (ret <= 0) return ret;
  }

  /* Assume sender is retrying the same data since he
   * must wait for an successful return before moving on
   * anyway. If we already encrypted and buffered the last
   * message, there's no way we can take it back if he cnages
   * his mind after a WANT_READ or a WANT_WRITE.
  */
  if (num > 0 && !ssl->write_pending) {
    if ((res = tls_write(ssl, buf, num)) <= 0) {
      return -1;
    }
    ssl->write_pending = 1;
  }
  if (!do_send(ssl)) return -1;

  ssl_err(ssl, SSL_ERROR_NONE);
  return res;
}

int SSL_get_error(const SSL *ssl, int ret) {
  (void) ret;
  return ssl->err;
}

int SSL_shutdown(SSL *ssl) {
  if (ssl->fatal) {
    return 0;
  }
  if (!ssl->close_notify) {
    switch (ssl->state) {
      default:
        dprintf(("sending close notify\n"));
        if (!tls_close_notify(ssl)) {
          dprintf(("failed to construct close_notify\n"));
          return -1;
        }

        kr_set_state(ssl, STATE_CLOSING);
        if (!do_send(ssl)) return -1;
      /* fall through */

      case STATE_CLOSING:
        while (!ssl->close_notify) {
          if (!do_recv(ssl, NULL, 0)) {
            return -1;
          }
        }
    }
  }
  return 1;
}

void SSL_free(SSL *ssl) {
  if (ssl) {
    tls_free_security(ssl->cur);
    tls_free_security(ssl->nxt);
    free(ssl->rx_buf);
    free(ssl->tx_buf);
    free(ssl);
  }
}

void ssl_err(SSL *ssl, int err) {
  switch (err) {
    case SSL_ERROR_NONE:
      break;
    case SSL_ERROR_SSL:
      break;
    case SSL_ERROR_WANT_READ:
      break;
    case SSL_ERROR_WANT_WRITE:
      break;
    case SSL_ERROR_SYSCALL:
      break;
    case SSL_ERROR_ZERO_RETURN:
      break;
    case SSL_ERROR_WANT_CONNECT:
      break;
    case SSL_ERROR_WANT_ACCEPT:
      break;
    default:
      abort();
  }
  dprintf(("ssl_err = %d\n", err));
  ssl->err = err;
}

NS_INTERNAL void kr_set_state(struct ssl_st *ssl, enum kr_state new_state) {
  dprintf(("state %d -> %d\n", ssl->state, new_state));
  ssl->state = new_state;
}
