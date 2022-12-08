#ifndef FILE_OPS_H__
#define FILE_OPS_H__

#define PATH_RESULT "/opt/0d1n/view/"
#define TABLE "/opt/0d1n/view/tables/output_array.txt"
#define TEMPLATE "/opt/0d1n/templates/template.conf"
#define TEMPLATE2 "/opt/0d1n/templates/hammer1.conf"
#define TEMPLATE3 "/opt/0d1n/templates/hammer2.conf"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <alloca.h>
#include "opt_extract.h"

void end_datatable(char * path);
void prepare_datatable(void);
char *read_lines(char * NameFile);
int write_file(char *file,char *str);
long file_size(const char *file);
char *Random_linefile(char * namefile);

#endif
