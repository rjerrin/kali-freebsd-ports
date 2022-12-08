#ifndef MEM_OPS_H__
#define MEM_OPS_H__

#include <stdio.h>	
#include <sys/types.h>
#include <string.h>		
#include <stdlib.h>
#include <time.h>
#include <curl/curl.h>
#include <stdint.h>
#include <assert.h>

#include "opt_extract.h"
#define XFREE(x) xfree((void **)&x); 
#define MUL_NO_OVERFLOW	((size_t)1 << (sizeof(size_t)*4))
// set DEBUG ON
#define BUGVIEW 1
#define DEBUG(x, s...) do { \
 if (!BUGVIEW) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "\n--- DEBUG-START ---\n\n %.*s %s[%d] %s(): \n", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
 fprintf(stderr,"\n\n--- DEBUG-END ---\n"); \
} while (0);
 
struct MemoryStruct {
  char *memory;
  size_t size;
};

typedef struct MemoryStruct MemoryStruct;

void free_global_buf();
void *xmalloc (size_t size);
void *xcalloc (size_t mem, size_t size);
void *xrealloc (void *ptr, size_t size);
void xfree(void **ptr);
size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);
int wait_on_socket(curl_socket_t sockfd, int for_recv, long timeout_ms);
void *xmallocarray (size_t nmemb, size_t size); 
void *xreallocarray (void *ptr, size_t nmemb, size_t size); 

#endif
