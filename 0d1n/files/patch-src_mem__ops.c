--- src/mem_ops.c.orig	2022-12-16 06:38:12 UTC
+++ src/mem_ops.c
@@ -17,7 +17,8 @@ xmalloc_fatal(size_t size) 
 xmalloc_fatal(size_t size) 
 {
 
-	DEBUG("\n Memory FAILURE...\n size dbg: %lu\n",size);
+
+    DEBUG("\n Memory FAILURE...\n size dbg: %zu\n",size);
 
 	exit(0);
 }
