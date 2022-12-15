--- src/strsec.c.orig	2022-12-09 02:57:38 UTC
+++ src/strsec.c
@@ -17,6 +17,9 @@
  */
 
 
+#include <string.h>
+#include <stdlib.h>
+
 #if !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__NetBSD__) && \
     !defined(__bsdi__) && !defined(__APPLE__)
 
@@ -155,7 +158,7 @@ char *xstrndup (const char *s, size_t n)
 
 char *xstrndup (const char *s, size_t n)
 {
-	char* new = xmalloc(n+1);
+	char* new = malloc(n+1);
 
 	if (new) 
 	{
