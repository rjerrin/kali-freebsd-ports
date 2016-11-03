--- ipv6.c.orig	2016-06-21 13:28:42 UTC
+++ ipv6.c
@@ -48,11 +48,6 @@
 
 #include <intrace.h>
 
-#undef in6_pktinfo
-struct in6_pktinfo {
-	struct in6_addr ipi6_addr;	/* src/dst IPv6 address */
-	unsigned int ipi6_ifindex;	/* send/recv interface index */
-};
 
 static uint16_t in_cksum(const uint16_t * addr, uint32_t len, uint32_t csum)
 {
