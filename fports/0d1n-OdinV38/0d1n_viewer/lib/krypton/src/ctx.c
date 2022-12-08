/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

#include "../openssl/ssl.h"
#include "ktypes.h"
#include "crypto.h"
#include "ber.h"
#include "x509.h"
#include "pem.h"

SSL_CTX *SSL_CTX_new(const SSL_METHOD *meth) {
  SSL_CTX *ctx;

  ctx = calloc(1, sizeof(*ctx));
  if (NULL == ctx) goto out;

  assert(meth != NULL);

  ctx->meth = *meth;

  /* success */
  goto out;

#if 0
out_free:
	free(ctx);
	ctx = NULL;
#endif
out:
  return ctx;
}

long SSL_CTX_ctrl(SSL_CTX *ctx, int cmd, long mode, void *ptr) {
  (void) ctx;
  (void) cmd;
  (void) ptr;
  if (cmd == 33) {
    ctx->mode |= mode;
  }
  return ctx->mode;
}

int SSL_CTX_set_cipher_list(SSL_CTX *ctx, const char *str) {
  /* TODO(rojer): Implement this. */
  (void) ctx;
  (void) str;
  return 0;
}

void SSL_CTX_set_verify(SSL_CTX *ctx, int mode,
                        int (*verify_callback)(int, X509_STORE_CTX *)) {
  /* not implemented */
  assert(verify_callback == NULL);
  (void) verify_callback;

  ctx->vrfy_mode = mode;
}

int SSL_CTX_kr_set_verify_name(SSL_CTX *ctx, const char *name) {
  free(ctx->verify_name);
  ctx->verify_name = strdup(name);
  return ctx->verify_name != NULL;
}

#ifdef KR_NO_LOAD_CA_STORE
static enum pem_filter_result pem_no_filter(const DER *obj, int type,
                                            void *arg) {
  (void) obj;
  (void) type;
  (void) arg;
  return PEM_FILTER_NO;
}
#endif

int SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *CAfile,
                                  const char *CAPath) {
  unsigned int i;
  int ret = 0;
  X509 *ca;
  PEM *p;

  /* not implemented */
  if (CAPath) {
    dprintf(("%s: CAPath: Not implemented\n", __func__));
  }
  if (NULL == CAfile) {
    /* XXX: SSL_error ?? */
    return 0;
  }

#ifndef KR_NO_LOAD_CA_STORE
  p = pem_load_types(CAfile, PEM_SIG_CERT);
  if (NULL == p) goto out;

  for (ca = NULL, i = 0; i < p->num_obj; i++) {
    DER *d = &p->obj[i];
    X509 *new;

    new = X509_new(d->der, d->der_len);
    if (NULL == new) goto out;

    new->next = ca;
    ca = new;
  }

  pem_free(p);
  X509_free(ctx->ca_store);
  ctx->ca_store = ca;
  ret = 1;
out:
  return ret;
#else /* KR_NO_LOAD_CA_STORE */
  (void) ca;
  (void) i;

  /* Do a dry-run through cert store. We'll get an empty store back. */
  p = pem_load(CAfile, pem_no_filter, NULL);
  if (p != NULL) {
    free(ctx->ca_file);
    ctx->ca_file = strdup(CAfile);
    pem_free(p);
    ret = 1;
  }
  return ret;
#endif
}

int SSL_CTX_use_certificate_chain_file(SSL_CTX *ctx, const char *file) {
  int ret = 0;
  PEM *p = NULL;

  p = pem_load_types(file, PEM_SIG_CERT);
  if (p == NULL) goto out;

  pem_free(ctx->pem_cert);
  ctx->pem_cert = p;
  ret = 1;
out:
  return ret;
}

int SSL_CTX_use_certificate_file(SSL_CTX *ctx, const char *file, int type) {
  int ret = 0;
  PEM *p = NULL;

  if (type != SSL_FILETYPE_PEM) {
    /* XXX: SSL_error */
    return 0;
  }

  p = pem_load_types(file, PEM_SIG_CERT);
  if (p == NULL) goto out;

  pem_free(ctx->pem_cert);
  ctx->pem_cert = p;
  ret = 1;
out:
  return ret;
}

static int decode_int(const uint8_t **pptr, const uint8_t *end,
                      struct ro_vec *result) {
  struct gber_tag tag;
  const uint8_t *ptr;

  ptr = ber_decode_tag(&tag, *pptr, end - *pptr);
  if (NULL == ptr) return 0;

  if (ber_id_octet_constructed(tag.ber_id)) return 0;

  result->ptr = ptr;
  result->len = tag.ber_len;
  *pptr = ptr + tag.ber_len;

  /* strip a trailing zero byte if it exists,
   * it's like a sign-byte or something?
  */
  if (result->len && !result->ptr[0]) {
    result->len--;
    result->ptr++;
  }

  return 1;
}

/*
RSAPrivateKey ::= SEQUENCE {
  version           Version,
  modulus           INTEGER,  -- n
  publicExponent    INTEGER,  -- e
  privateExponent   INTEGER,  -- d
  prime1            INTEGER,  -- p
  prime2            INTEGER,  -- q
  exponent1         INTEGER,  -- d mod (p-1)
  exponent2         INTEGER,  -- d mod (q-1)
  coefficient       INTEGER,  -- (inverse of q) mod p
  otherPrimeInfos   OtherPrimeInfos OPTIONAL
}
*/
int SSL_CTX_use_PrivateKey_file(SSL_CTX *ctx, const char *file, int type) {
  struct ro_vec vers, n, e, d, p, q, e1, e2, c;
  const uint8_t *ptr, *end;
  struct gber_tag tag;
  RSA_CTX *rsa = NULL;
  int ret = 0;
  PEM *pem;

  if (type != SSL_FILETYPE_PEM) {
    return 0;
  }

  pem = pem_load_types(file, PEM_SIG_KEY | PEM_SIG_RSA_KEY);
  if (NULL == pem) goto out;

  ptr = pem->obj[0].der;
  end = ptr + pem->obj[0].der_len;

  if (pem->obj[0].der_type == PEM_SIG_KEY) {
    const uint8_t *ai;
    static const char *const oidAlgoRSA =
        "\x2a\x86\x48\x86\xf7\x0d\x01\x01\x01"; /* 1.2.840.113549.1.1.1 */

    ptr = ber_decode_tag(&tag, ptr, end - ptr);
    if (NULL == ptr || !ber_id_octet_constructed(tag.ber_id)) goto decode_err;

    /* Version */
    if (!decode_int(&ptr, end, &vers)) goto decode_err;

    /* Verify that PrivateKeyInfo.algorithm is RSA */
    ai = ber_decode_tag(&tag, ptr, end - ptr);
    if (NULL == ai || !ber_id_octet_constructed(tag.ber_id)) goto decode_err;
    ptr = ai + tag.ber_len;

    ai = ber_decode_tag(&tag, ai, end - ai);
    if (NULL == ai || tag.ber_tag != 6 /* OID */ || tag.ber_len != 9 ||
        memcmp(ai, oidAlgoRSA, 9) != 0) {
      goto decode_err;
    }
    ai += 9;

    /* Ok, it's RSA. Unwrap the key and continue. */
    ptr = ber_decode_tag(&tag, ptr, end - ptr);
    if (NULL == ptr || tag.ber_tag != 4 /* octet string */) goto decode_err;
  }

  ptr = ber_decode_tag(&tag, ptr, end - ptr);
  if (NULL == ptr || !ber_id_octet_constructed(tag.ber_id)) goto decode_err;

  /* eat the version */
  if (!decode_int(&ptr, end, &vers)) goto decode_err;
  if (!decode_int(&ptr, end, &n)) goto decode_err;
  if (!decode_int(&ptr, end, &e)) goto decode_err;
  if (!decode_int(&ptr, end, &d)) goto decode_err;
  if (!decode_int(&ptr, end, &p)) goto decode_err;
  if (!decode_int(&ptr, end, &q)) goto decode_err;
  if (!decode_int(&ptr, end, &e1)) goto decode_err;
  if (!decode_int(&ptr, end, &e2)) goto decode_err;
  if (!decode_int(&ptr, end, &c)) goto decode_err;

  RSA_priv_key_new(&rsa, n.ptr, n.len, e.ptr, e.len, d.ptr, d.len, p.ptr, p.len,
                   q.ptr, q.len, e1.ptr, e1.len, e2.ptr, e2.len, c.ptr, c.len);
  if (NULL == rsa) goto out_free_pem;

  RSA_free(ctx->rsa_privkey);
  ctx->rsa_privkey = rsa;
  ret = 1;
  goto out_free_pem;

decode_err:
  dprintf(("%s: RSA private key decode error\n", file));
out_free_pem:
  pem_free(pem);
out:
  return ret;
}

void SSL_CTX_free(SSL_CTX *ctx) {
  if (ctx == NULL) return;
#ifndef KR_NO_LOAD_CA_STORE
  X509_free(ctx->ca_store);
#else
  free(ctx->ca_file);
#endif
  pem_free(ctx->pem_cert);
  RSA_free(ctx->rsa_privkey);
  free(ctx->verify_name);
  free(ctx);
}
