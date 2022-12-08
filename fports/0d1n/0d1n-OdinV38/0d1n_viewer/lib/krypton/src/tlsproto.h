/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_KRYPTON_SRC_TLSPROTO_H_
#define CS_KRYPTON_SRC_TLSPROTO_H_

/* set to number of null ciphers */
#define KR_ALLOW_NULL_CIPHERS 0

/* just count non-NULL ciphers */
#define NUM_CIPHER_SUITES 4

#define NUM_COMPRESSORS 1

#pragma pack(1)
struct tls_random {
  uint32_t time;
  uint8_t opaque[28];
} __packed;

struct tls_premaster_secret {
  uint16_t version;
  uint8_t opaque[46];
} __packed;

struct tls_hmac_hdr {
  uint64_t seq;
  uint8_t type;
  uint16_t vers;
  uint16_t len;
} __packed;

struct tls_hdr {
  uint8_t type;
  uint16_t vers;
  uint16_t len;
} __packed;

struct tls_EXT_reneg {
  uint16_t type;
  uint16_t len;
  uint8_t ri_len;
} __packed;

struct tls_svr_hello {
  uint8_t type;
  uint8_t len_hi;
  uint16_t len;
  uint16_t version;
  struct tls_random random;
  uint8_t sess_id_len;
  uint16_t cipher_suite;
  uint8_t compressor;
  uint16_t ext_len;

  struct tls_EXT_reneg ext_reneg;
} __packed;

struct tls_cl_hello {
  uint8_t type;
  uint8_t len_hi;
  uint16_t len;
  uint16_t version;
  struct tls_random random;
  uint8_t sess_id_len;
  uint16_t cipher_suites_len;
  uint16_t cipher_suite[NUM_CIPHER_SUITES + KR_ALLOW_NULL_CIPHERS + 1];
  uint8_t num_compressors;
  uint8_t compressor[NUM_COMPRESSORS];
  uint16_t ext_len;

  struct tls_EXT_reneg ext_reneg;
} __packed;

struct tls_cert {
  uint8_t type;
  uint8_t len_hi;
  uint16_t len;
  uint8_t certs_len_hi;
  uint16_t certs_len;
} __packed;

struct tls_cert_hdr {
  /* for chains */
  uint8_t cert_len_hi;
  uint16_t cert_len;
} __packed;

struct tls_svr_hello_done {
  uint8_t type;
  uint8_t len_hi;
  uint16_t len;
} __packed;

struct tls_change_cipher_spec {
  uint8_t one;
} __packed;

struct tls_finished {
  uint8_t type;
  uint8_t len_hi;
  uint16_t len;
  uint8_t vrfy[12];
} __packed;

struct tls_alert {
  uint8_t level;
  uint8_t desc;
} __packed;
#pragma pack()

enum TLS_HashAlgorithm {
  TLS_HASH_SHA256 = 4,
};

enum TLS_SignatureAlgorithm {
  TLS_SIG_RSA = 1,
};

#define TLS_1_2_PROTO 0x0303
#define TLS_1_1_PROTO 0x0302
#define TLS_1_0_PROTO 0x0301
#define SSL_3_0_PROTO 0x0300

#define TLS_CHANGE_CIPHER_SPEC 20
#define TLS_ALERT 21
#define TLS_HANDSHAKE 22
#define TLS_APP_DATA 23
#define TLS_HEARTBEAT 24

#define HANDSHAKE_HELLO_REQ 0
#define HANDSHAKE_CLIENT_HELLO 1
#define HANDSHAKE_SERVER_HELLO 2
#define HANDSHAKE_NEW_SESSION_TICKET 4
#define HANDSHAKE_CERTIFICATE 11
#define HANDSHAKE_SERVER_KEY_EXCH 12
#define HANDSHAKE_CERTIFICATE_REQ 13
#define HANDSHAKE_SERVER_HELLO_DONE 14
#define HANDSHAKE_CERTIFICATE_VRFY 15
#define HANDSHAKE_CLIENT_KEY_EXCH 16
#define HANDSHAKE_FINISHED 20

#define EXT_SERVER_NAME 0x0000
#define EXT_SESSION_TICKET 0x0023
#define EXT_HEARTBEAT 0x000f
#define EXT_SIG_ALGOS 0x000d
#define EXT_NPN 0x3374
#define EXT_RENEG_INFO 0xff01

#define ALERT_LEVEL_WARNING 1
#define ALERT_LEVEL_FATAL 2

#define ALERT_CLOSE_NOTIFY 0
#define ALERT_UNEXPECTED_MESSAGE 10
#define ALERT_BAD_RECORD_MAC 20
#define ALERT_RECORD_OVERFLOW 22
#define ALERT_HANDSHAKE_FAILURE 40
#define ALERT_BAD_CERT 42
#define ALERT_UNSUPPORTED_CERT 43
#define ALERT_CERT_REVOKED 44
#define ALERT_CERT_EXPIRED 43
#define ALERT_CERT_UNKNOWN 46
#define ALERT_ILLEGAL_PARAMETER 47
#define ALERT_UNKNOWN_CA 48
#define ALERT_ACCESS_DENIED 49
#define ALERT_DECODE_ERROR 50
#define ALERT_DECRYPT_ERROR 51
#define ALERT_PROTOCOL_VERSION 70
#define ALERT_INSUFFICIENT_SECURITY 71
#define ALERT_INTERNAL_ERROR 80
#define ALERT_USER_CANCELLED 90
#define ALERT_NO_RENEGOTIATION 100
#define ALERT_UNSUPPORTED_EXT 110

/* http://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-4
 */

typedef enum {
#if KR_ALLOW_NULL_CIPHERS
  TLS_RSA_WITH_NULL_MD5 = 0x0001,
#endif
  TLS_RSA_WITH_RC4_128_MD5 = 0x0004,
  TLS_RSA_WITH_RC4_128_SHA = 0x0005,
  TLS_RSA_WITH_AES_128_CBC_SHA = 0x002f,
  TLS_RSA_WITH_AES_128_CBC_SHA256 = 0x003c,
} kr_cs_id;

#define TLS_EMPTY_RENEGOTIATION_INFO_SCSV 0x00ff

#define COMPRESSOR_NULL 0x00

#endif /* CS_KRYPTON_SRC_TLSPROTO_H_ */
