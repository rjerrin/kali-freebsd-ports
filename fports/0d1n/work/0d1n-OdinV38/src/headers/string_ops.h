#ifndef STRING_OPS_H__
#define STRING_OPS_H__

#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>

//#include "mem_ops.h"
#define XorSwap(a, b) (((*a) ^= (*b)), ((*b) ^= (*a)), ((*a) ^= (*b)))
                        
void deadspace(char *str);
void *entropy_clock(void);
int total_lines_of_buffer(char *list);	
char *random_line_of_buffer(char *list, int lines_total);
char *rand_str(char *dst, int size);
char *rand_number(char *dst, int size);
int char_type_counter(char *string,char type);
void chomp(char * str);
char *payload_injector(char * ptr,char * payload,int counter);
int strstr_regex(char *string, char *expression); // todo replace pcre to re2 library
char *replace(char *instring,char *old,char *new);
long parse_http_status(char * str);

#endif
