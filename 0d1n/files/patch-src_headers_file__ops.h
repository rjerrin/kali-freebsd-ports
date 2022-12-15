--- src/headers/file_ops.h.orig	2022-07-10 02:56:04 UTC
+++ src/headers/file_ops.h
@@ -1,18 +1,17 @@
 #ifndef FILE_OPS_H__
 #define FILE_OPS_H__
 
-#define PATH_RESULT "/opt/0d1n/view/"
-#define TABLE "/opt/0d1n/view/tables/output_array.txt"
-#define TEMPLATE "/opt/0d1n/templates/template.conf"
-#define TEMPLATE2 "/opt/0d1n/templates/hammer1.conf"
-#define TEMPLATE3 "/opt/0d1n/templates/hammer2.conf"
+#define PATH_RESULT "/usr/local/share/data/0d1n/view/"
+#define TABLE      "/usr/local/share/data/0d1n/output_array.txt"
+#define TEMPLATE  "/usr/local/share/data/templates/template.conf"
+#define TEMPLATE2 "/usr/loal/share/data/templates/hammer1.conf"
+#define TEMPLATE3 "/usr/local/share/data/templates/hammer2.conf"
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <errno.h>
-#include <alloca.h>
 #include "opt_extract.h"
 
 void end_datatable(char * path);
