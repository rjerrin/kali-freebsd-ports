/*
 * Copyright (c) 2015 Cesanta Software Limited
 * All rights reserved
 */

#include "ktypes.h"

#ifdef KR_RANDOM_SOURCE_FILE
int kr_get_random(uint8_t *out, size_t len) {
  static FILE *fp = NULL;
  size_t ret = 0;

  if (fp == NULL) {
    /* TODO(lsm): provide cleanup API  */
    fp = fopen(KR_RANDOM_SOURCE_FILE, "rb");
  }

  if (fp != NULL) {
    ret = fread(out, 1, len, fp);
  } else {
    dprintf(("failed to open %s\n", KR_RANDOM_SOURCE_FILE));
  }

  return ret == len;
}
#elif defined(KR_USE_RAND)
int kr_get_random(uint8_t *out, size_t len) {
  static int srand_called = 0;
  if (!srand_called) {
    /* Mix in our pointer. In case user did not invoke srand(), this is better
     * than nothing. If he did, this will not totally screw it up. */
    srand(rand() ^ ((int) (out + len)));
    srand_called = 1;
  }
  while (len-- > 0) {
    *(out++) = (uint8_t) rand();
  }
  return 1;
}
#endif

int get_random_nonzero(uint8_t *out, size_t len) {
  size_t i;

  if (!kr_get_random(out, len)) return 0;

  for (i = 0; i < len; i++) {
    while (out[i] == 0) {
      if (!kr_get_random(out + i, 1)) return 0;
    }
  }

  return 1;
}
