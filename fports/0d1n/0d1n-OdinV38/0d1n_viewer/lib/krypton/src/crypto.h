/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_KRYPTON_SRC_CRYPTO_H_
#define CS_KRYPTON_SRC_CRYPTO_H_

NS_INTERNAL int get_random_nonzero(uint8_t *out, size_t len);

/* axTLS crypto functions, see C files for copyright info */
typedef struct _SHA256_CTX SHA256_CTX;

NS_INTERNAL void prf(const uint8_t *sec, size_t sec_len, const uint8_t *seed,
                     size_t seed_len, uint8_t *out, size_t olen);

/* SHA256 */
#define SHA256_SIZE 32
#define SHA256_BLOCK_LENGTH 64
struct _SHA256_CTX {
  uint32_t state[8];
  uint64_t bitcount;
  uint8_t buffer[SHA256_BLOCK_LENGTH];
};

NS_INTERNAL void SHA256_Init(SHA256_CTX *c);
NS_INTERNAL void SHA256_Update(SHA256_CTX *, const uint8_t *input, size_t len);
NS_INTERNAL void SHA256_Final(uint8_t digest[32], SHA256_CTX *);

#define SHA1_SIZE 20
#define MD5_SIZE 16
#define MAX_DIGEST_SIZE SHA256_SIZE

#define AES_IV_SIZE 16
#define MAX_IV_SIZE AES_IV_SIZE

#define RC4_KEY_SIZE 16
#define AES128_KEY_SIZE 16
#define AES256_KEY_SIZE 32
#define MAX_KEY_SIZE AES256_KEY_SIZE

/* RSA */
NS_INTERNAL void RSA_priv_key_new(RSA_CTX **rsa_ctx, const uint8_t *modulus,
                                  int mod_len, const uint8_t *pub_exp,
                                  int pub_len, const uint8_t *priv_exp,
                                  int priv_len, const uint8_t *p, int p_len,
                                  const uint8_t *q, int q_len,
                                  const uint8_t *dP, int dP_len,
                                  const uint8_t *dQ, int dQ_len,
                                  const uint8_t *qInv, int qInv_len);
NS_INTERNAL void RSA_pub_key_new(RSA_CTX **rsa_ctx, const uint8_t *modulus,
                                 int mod_len, const uint8_t *pub_exp,
                                 int pub_len);
NS_INTERNAL void RSA_free(RSA_CTX *ctx);
NS_INTERNAL int RSA_decrypt(const RSA_CTX *ctx, const uint8_t *in_data,
                            uint8_t *out_data, int out_len, int is_decryption);
NS_INTERNAL bigint *RSA_private(const RSA_CTX *c, bigint *bi_msg);
NS_INTERNAL int RSA_encrypt(const RSA_CTX *ctx, const uint8_t *in_data,
                            uint16_t in_len, uint8_t *out_data, int is_signing);
NS_INTERNAL bigint *RSA_public(const RSA_CTX *c, bigint *bi_msg);
NS_INTERNAL int RSA_block_size(RSA_CTX *ctx);
#if defined(CONFIG_SSL_CERT_VERIFICATION) || \
    defined(CONFIG_SSL_GENERATE_X509_CERT)
NS_INTERNAL bigint *RSA_sign_verify(BI_CTX *ctx, const uint8_t *sig,
                                    int sig_len, bigint *modulus,
                                    bigint *pub_exp);
NS_INTERNAL void RSA_print(const RSA_CTX *ctx);
#endif

/* Faster modular arithmetic, bigger code */
#define CONFIG_BIGINT_BARRETT 1

/* faster multiplies, bigger code, only worth it for bigger keys or systems
 * with very slow multiplys. Not worth it on x86.
*/
/* #define CONFIG_BIGINT_KARATSUBA 1 */
#define MUL_KARATSUBA_THRESH 20
#define SQU_KARATSUBA_THRESH 40

NS_INTERNAL int kr_hmac_len(kr_cs_id cs);

/* cs = 0 -> client MAC, cs = 1 -> server MAC. */
#define KR_CLIENT_MAC 0
#define KR_SERVER_MAC 1
NS_INTERNAL void kr_ssl_hmac(SSL *ssl, int cs, size_t num_msgs,
                             const uint8_t *msgs[], const size_t *msg_lens,
                             uint8_t *digest);

typedef void (*kr_hash_func_t)(size_t, const uint8_t **, const size_t *,
                               uint8_t *);
NS_INTERNAL void kr_hmac_v(kr_hash_func_t hash_func, const uint8_t *key,
                           size_t key_len, size_t num_msgs,
                           const uint8_t *msgs[], const size_t *msg_lens,
                           uint8_t *digest, size_t digest_len);

NS_INTERNAL const kr_cipher_info *kr_cipher_get_info(kr_cs_id cs);

NS_INTERNAL void kr_cbc_encrypt(const kr_cipher_info *ci, void *cctx,
                                const uint8_t *msg, int len, const uint8_t *iv,
                                uint8_t *out);
NS_INTERNAL void kr_cbc_decrypt(const kr_cipher_info *ci, void *cctx,
                                const uint8_t *msg, int len, const uint8_t *iv,
                                uint8_t *out);

const kr_cipher_info *kr_rc4_cs_info();
const kr_cipher_info *kr_aes128_cs_info();

#endif /* CS_KRYPTON_SRC_CRYPTO_H_ */
