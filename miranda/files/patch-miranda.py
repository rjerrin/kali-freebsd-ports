--- miranda.py.orig	2016-11-03 08:03:27 UTC
+++ miranda.py
@@ -19,6 +19,7 @@ try:
 	import base64
 	import re
 	import getopt
+        import netifaces
 except Exception,e:
 	print 'Unmet dependency:',e
 	sys.exit(1)
@@ -59,7 +60,9 @@ class cmdCompleter:
 class upnp:
 	ip = False
 	port = False
+        addrinfo = None
 	completer = False
+        ttl_bin = 2
 	msearchHeaders = {
 		'MAN' : '"ssdp:discover"',
 		'MX'  : '2'
@@ -78,11 +81,12 @@ class upnp:
 	STARS = '****************************************************************'
 	csock = False
 	ssock = False
+        MYTTL = 2 
 
-	def __init__(self,ip,port,iface,appCommands):
+	def __init__(self,ip,port,appCommands):
 		if appCommands:
 			self.completer = cmdCompleter(appCommands)
-		if self.initSockets(ip,port,iface) == False:
+		if self.initSockets(ip,port) == False:
 			print 'UPNP class initialization failed!'
 			print 'Bye!'
 			sys.exit(1)
@@ -90,14 +94,11 @@ class upnp:
 			self.soapEnd = re.compile('<\/.*:envelope>')
 
 	#Initialize default sockets
-	def initSockets(self,ip,port,iface):
+	def initSockets(self,ip,port):
 		if self.csock:
 			self.csock.close()
 		if self.ssock:
 			self.ssock.close()
-
-		if iface != None:
-			self.IFACE = iface
 		if not ip:
                 	ip = self.DEFAULT_IP
                 if not port:
@@ -106,35 +107,42 @@ class upnp:
                 self.ip = ip
 		
 		try:
-			#This is needed to join a multicast group
-			self.mreq = struct.pack("4sl",inet_aton(ip),INADDR_ANY)
-
-			#Set up client socket
-			self.csock = socket(AF_INET,SOCK_DGRAM)
-			self.csock.setsockopt(IPPROTO_IP,IP_MULTICAST_TTL,2)
+                        self.addrinfo = getaddrinfo(self.ip,None)[0]
+                        ttl_bin = struct.pack('@i',self.MYTTL)
+                        self.csock = socket(self.addrinfo[0], SOCK_DGRAM)
+                        if self.addrinfo[0] == AF_INET: # IPv4
+                                self.csock.setsockopt(IPPROTO_IP, IP_MULTICAST_TTL, ttl_bin)
+                        else: #IPv6
+                                self.csock.setsockopt(IPPROTO_IPV6,IPV6_MULTICAST_HOPS,ttl_bin)
 			
 			#Set up server socket
-			self.ssock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)
+			self.ssock = socket(self.addrinfo[0],SOCK_DGRAM)
 			self.ssock.setsockopt(SOL_SOCKET,SO_REUSEADDR,1)
+                        group_bin = inet_pton(self.addrinfo[0], self.addrinfo[4][0])
 			
-			#Only bind to this interface
-			if self.IFACE != None:
-				print '\nBinding to interface',self.IFACE,'...\n'
-				self.ssock.setsockopt(SOL_SOCKET,IN.SO_BINDTODEVICE,struct.pack("%ds" % (len(self.IFACE)+1,), self.IFACE))
-				self.csock.setsockopt(SOL_SOCKET,IN.SO_BINDTODEVICE,struct.pack("%ds" % (len(self.IFACE)+1,), self.IFACE))
-
 			try:
-				self.ssock.bind(('',self.port))
+				self.ssock.bind(( '',self.port ))
+                          
 			except Exception, e:
 				print "WARNING: Failed to bind %s:%d: %s" , (self.ip,self.port,e)
 			try:
-				self.ssock.setsockopt(IPPROTO_IP,IP_ADD_MEMBERSHIP,self.mreq)
-			except Exception, e:
+                                group_bin = inet_pton(self.addrinfo[0], self.addrinfo[4][0])
+                                if self.addrinfo[0] == AF_INET:
+                                        mreq = group_bin + struct.pack('=I', INADDR_ANY)
+                                        self.ssock.setsockopt(IPPROTO_IP,IP_ADD_MEMBERSHIP,mreq)
+                                else:
+                                        mreq = group_bin + struct.pack('@I', 0)
+                                        print mreq
+                                        s.setsockopt(IPPROTO_IPV6, IPV6_JOIN_GROUP, mreq)
+
+                                        
+		        except Exception, e:
 				print 'WARNING: Failed to join multicast group:',e
 		except Exception, e:
 			print "Failed to initialize UPNP sockets:",e
 			return False
-		return True
+
+                return True
 
 	#Clean up file/socket descriptors
 	def cleanup(self):
@@ -281,6 +289,7 @@ class upnp:
 				messageType = False
 
 		#If this is a notification or a reply message...
+
 		if messageType != False:
 			#Get the host name and location of it's main UPNP XML file
 			xmlFile = self.parseHeader(data,"LOCATION")
@@ -795,7 +804,7 @@ def msearch(argc,argv,hp):
 	defaultST = "upnp:rootdevice"
 	st = "schemas-upnp-org"
 	myip = ''
-	lport = hp.port
+	lport = 1901
 
 	if argc >= 3:
 		if argc == 4:
@@ -899,17 +908,8 @@ def seti(argc,argv,hp):
 			else:
 				showHelp(argv[0])
 			return
-		elif action == 'iface':
-			if argc == 3:
-				hp.IFACE = argv[2]
-				print 'Interface set to %s, re-binding sockets...' % hp.IFACE
-				if hp.initSockets(hp.ip,hp.port,hp.IFACE):
-					print 'Interface change successful!'
-				else:
-					print 'Failed to bind new interface - are you sure you have root privilages??'
-					hp.IFACE = None
-				return
-		elif action == 'socket':
+	
+	        elif action == 'socket':
 			if argc == 3:
 				try:
 					(ip,port) = argv[2].split(':')
@@ -917,7 +917,7 @@ def seti(argc,argv,hp):
 					hp.ip = ip
 					hp.port = port
 					hp.cleanup()
-					if hp.initSockets(ip,port,hp.IFACE) == False:
+					if hp.initSockets(ip,port) == False:
 						print "Setting new socket %s:%d failed!" % (ip,port)
 					else:
 						print "Using new socket: %s:%d" % (ip,port)
@@ -1518,40 +1518,8 @@ def parseCliOpts(argc,argv,hp):
 				print 'Verbose mode enabled!'
 			elif opt == '-h':
 				usage()
-			elif opt == '-i':
-				networkInterfaces = []
-				requestedInterface = arg
-				interfaceName = None
-				found = False
 
-				#Get a list of network interfaces. This only works on unix boxes.
-				try:
-					if thisSystem() != 'Windows':
-						fp = open('/proc/net/dev','r')
-						for line in fp.readlines():
-							if ':' in line:
-								interfaceName = line.split(':')[0].strip()
-								if interfaceName == requestedInterface:
-									found = True
-									break
-								else:
-									networkInterfaces.append(line.split(':')[0].strip())
-						fp.close()
-					else:
-						networkInterfaces.append('Run ipconfig to get a list of available network interfaces!')
-				except Exception,e:
-					print 'Error opening file:',e
-					print "If you aren't running Linux, this file may not exist!"
-					
-				if not found and len(networkInterfaces) > 0:
-					print "Failed to find interface '%s'; try one of these:\n" % requestedInterface
-					for iface in networkInterfaces:
-						print iface
-					print ''
-					sys.exit(1)
-				else:
-					if not hp.initSockets(False,False,interfaceName):
-						print 'Binding to interface %s failed; are you sure you have root privilages??' % interfaceName
+                hp.initSockets(False,False)
 
 #Toggle boolean values
 def toggleVal(val):
@@ -1651,7 +1619,7 @@ def main(argc,argv):
                 appCommands['load'][file] = None
 
 	#Initialize upnp class
-	hp = upnp(False,False,None,appCommands);
+	hp = upnp(False,False,appCommands);
 
 	#Set up tab completion and command history
 	readline.parse_and_bind("tab: complete")
