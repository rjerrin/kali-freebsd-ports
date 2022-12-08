#ifndef TAMPER_H__
#define TAMPER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdint.h>
//#include "mem_ops.h"
#include "string_ops.h"
#include "validate.h"
#include "strsec.h"
#include "stdbool.h"

char * tamper_choice(char * tamper,char * line);
char* encode64(char* input, int len);
char *rand_case(char *str); 
char *urlencode(char *str); 
char *double_urlencode( char *str);
char *spaces2comment(char *str);
char *unmagicquote(char *str);
char *apostrophe2nullencode(char *str);
char *rand_comment(char *str);
char *rand_space(char *str);
char *replace_keywords(char *str);

#endif
