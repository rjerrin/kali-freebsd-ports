#ifndef GET_CSRF_TOKEN_H__
#define GET_CSRF_TOKEN_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <curl/curl.h>
#include <curl/easy.h>

#include "spider.h"
#include "string_ops.h"
#include "mem_ops.h"
#include "string_ops.h"
#include "opt_extract.h"
/*
THis function get anti csrf token of param var
*/

char *insert_csrf_token(char *payload, char *token_name, char *token);
char *parse_token(char *str);
char *get_anti_csrf_token(char *url, char *name_token);
char *prepare_url(char * url);

#endif
