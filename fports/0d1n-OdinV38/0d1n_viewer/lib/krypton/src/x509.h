/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_KRYPTON_SRC_X509_H_
#define CS_KRYPTON_SRC_X509_H_

#define X509_ENC_ALG_UNKNOWN 0
#define X509_ENC_ALG_RSA 1

#define X509_HASH_MD5 0x04
#define X509_HASH_SHA1 0x05
#define X509_HASH_SHA256 0x0b

struct X509_st {
  X509 *next;
  RSA_CTX *pub_key;

  struct vec issuer;
  struct vec subject;
  struct vec sig;
  struct vec alt_names; /* encoded */

  uint8_t enc_alg;

  /* both must be RSA + something */
  uint8_t hash_alg;
  uint8_t issuer_hash_alg;

  uint8_t is_self_signed : 1;
  uint8_t is_ca : 1;

  uint8_t digest[MAX_DIGEST_SIZE];
};

NS_INTERNAL X509 *X509_new(const uint8_t *ptr, size_t len);
/* chain should be backwards with subject at the end */
NS_INTERNAL int X509_verify(SSL_CTX *ctx, X509 *chain);
NS_INTERNAL void X509_free(X509 *cert);

NS_INTERNAL int x509_issued_by(struct vec *issuer, struct vec *subject);
NS_INTERNAL int X509_verify_name(X509 *cert, const char *name);

NS_INTERNAL int kr_match_domain_name(struct ro_vec pat, struct ro_vec dom);

#endif /* CS_KRYPTON_SRC_X509_H_ */
