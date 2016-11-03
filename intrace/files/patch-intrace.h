--- intrace.h.orig	2016-06-21 13:22:20 UTC
+++ intrace.h
@@ -65,7 +65,7 @@ typedef struct {
 
 #define _IT_AF(i) (i->isIPv6 ? AF_INET6 : AF_INET)
 #define _IT_IPPROTO(i) (i->isIPv6 ? IPPROTO_IPV6 : IPPROTO_IP)
-#define _IT_PKTINFO(i) (i->isIPv6 ? IPV6_RECVPKTINFO : IP_PKTINFO)
+#define _IT_PKTINFO(i) (i->isIPv6 ? IPV6_RECVPKTINFO :  IP_SENDSRCADDR)
 #define _IT_ICMPPROTO(i) (i->isIPv6 ? IPPROTO_ICMPV6 : IPPROTO_ICMP)
 #define _IT_LIP(i) (i->isIPv6 ? (void*)i->lip6.s6_addr : (void*)&i->lip.s_addr)
 #define _IT_RIP(i) (i->isIPv6 ? (void*)i->rip6.s6_addr : (void*)&i->rip.s_addr)
