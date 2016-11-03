--- sender.h.orig	2016-10-22 10:28:26 UTC
+++ sender.h
@@ -6,11 +6,10 @@
 #define _SENDER_H_
 
 /* For FreeBSD/Sorlaris */
-//#include <netinet/in_systm.h>
-
-//#include <netinet/in.h>
-//#include <netinet/tcp.h>
-//#include <netinet/ip.h>
+#include <netinet/in_systm.h>
+#include <netinet/in.h>
+#include <netinet/tcp.h>
+#include <netinet/ip.h>
 
 #define MAX_PAYL_SZ 256
 
