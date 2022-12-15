--- src/0d1n.c.orig	2022-12-09 02:48:56 UTC
+++ src/0d1n.c
@@ -61,14 +61,7 @@ main (int argc, char ** argv)
 // this source code have a different scan() function to bypass the compiler bug
 /* remove comment to test the patch
 */
-#ifdef __GNUC__
-#  if __GNUC_PREREQ(10,0)
 
-	scan_gcc_new();
-#  else
-	scan_gcc_old();
-#  endif
-#endif
 
  	exit(0);
 }
