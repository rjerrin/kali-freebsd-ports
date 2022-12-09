#ifndef SPIDER_H__
#define SPIDER_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <alloca.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <curl/curl.h>
//#include <curl/types.h>
#include <curl/easy.h>

#include "results.h"
#include "mem_ops.h"
#include "html_entities.h" 
#include "string_ops.h"
#include "file_ops.h"
#include "tamper.h"
#include "get_csrf_token.h"
#include "opt_extract.h"

struct curl_slist *keep_alive_generate(struct curl_slist *headers);
void spider(void *in);

#endif
