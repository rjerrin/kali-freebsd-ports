/*
 * Copyright (c) 2010 Gianni Tedesco <gianni@scaramanga.co.uk>
 * Released under the MIT license.
 */

#ifndef CS_KRYPTON_SRC_BER_H_
#define CS_KRYPTON_SRC_BER_H_

typedef uint16_t gber_tag_t;

struct gber_tag {
  size_t ber_len;
  gber_tag_t ber_tag;
  uint8_t ber_id;
};

#define GBER_CLASS_UNIVERSAL 0
#define GBER_CLASS_APPLICATION 1
#define GBER_CLASS_CONTEXT 2
#define GBER_CLASS_PRIVATE 3

/* returns start of data if present or NULL if truncated */
NS_INTERNAL const uint8_t *ber_decode_tag(struct gber_tag *tag,
                                          const uint8_t *ptr, size_t len);
NS_INTERNAL unsigned int ber_id_octet_constructed(uint8_t id);
#if 0
NS_INTERNAL const uint8_t *ber_tag_info(struct gber_tag *tag,
				const uint8_t *ptr, size_t len);
NS_INTERNAL unsigned int ber_id_octet_class(uint8_t id);
#endif

#if KRYPTON_DEBUG
NS_INTERNAL const char *ber_id_octet_clsname(uint8_t id);
int ber_dump(const uint8_t *ptr, size_t len);
int ber_dumpf(FILE *f, const uint8_t *ptr, size_t len);
#endif

#endif /* CS_KRYPTON_SRC_BER_H_ */
