--- goofile.py.orig	2016-10-21 16:35:07 UTC
+++ goofile.py
@@ -1,4 +1,4 @@
-#!/usr/bin/env python
+#!/usr/local/bin/python 
 # Goofile v1.5
 # My Website: http://www.g13net.com
 # Project Page: http://code.google.com/p/goofile
@@ -8,7 +8,7 @@
 # 
 
 import string
-import httplib
+import requests
 import sys
 import re
 import getopt
@@ -20,11 +20,9 @@ print "|www.g13net.com                  
 print "|code.google.com/p/goofile          |"
 print "-------------------------------------\n\n"
 
-global result
 result =[]
 
 def usage():
- print "Goofile 1.5\n"
  print "usage: goofile options \n"
  print "       -d: domain to search\n"
  print "       -f: filetype (ex. pdf)\n"
@@ -32,26 +30,20 @@ def usage():
  sys.exit()
 
 def run(dmn,file):
+ google_domain = 'www.google.com'
+ search_query = "/search?&q=site:"+ dmn + "+filetype:" + file + "&filter=0"
+ url = 'http://' + google_domain + search_query
+ try:
+  data = requests.get(url,timeout=20)
+ except :
+  print "Error loading url %s\n"  % url
+  sys.exit(1)
+
+ return [ url for url  in  re.findall('url\?q=(.+?)&',data.text) ]
+
 
-	h = httplib.HTTP('www.google.com')
-	h.putrequest('GET',"/search?num=500&q=site:"+dmn+"+filetype:"+file)
-	h.putheader('Host', 'www.google.com')
-	h.putheader('User-agent', 'Internet Explorer 6.0 ')
-	h.putheader('Referrer', 'www.g13net.com')
-	h.endheaders()
-	returncode, returnmsg, headers = h.getreply()
-	data=h.getfile().read()
-	data=re.sub('<b>','',data)
-        for e in ('>','=','<','\\','(',')','"','http',':','//'):
-		data = string.replace(data,e,' ')
-	r1 = re.compile('[-_.a-zA-Z0-9.-_]*'+'\.'+file)	
-	res = r1.findall(data) 
-	return res 
-	
 
 def search(argv):
-	global limit
-	limit = 100
 	if len(sys.argv) < 2: 
 		usage() 
 	try :
@@ -59,6 +51,7 @@ def search(argv):
  
 	except getopt.GetoptError:
   	     	usage()
+                print "opt error\n"
 		sys.exit()
 	
 	for opt,arg in opts :
@@ -69,35 +62,28 @@ def search(argv):
 	
 	print "Searching in "+dmn+" for "+ file
 	print "========================================"
+        data = run(dmn,file)
+	for x in data:
+         if re.search("\.%s$" % file, x,re.UNICODE ):
+	  if result.count(x) == 0:
+           result.append(x)
 
-
-	cant = 0
-
-	while cant < limit:
-		res = run(dmn,file)
-		for x in res:
-			if result.count(x) == 0:
-        			result.append(x)
-		cant+=100
-			
-
-	print "\nFiles found:"
+        print "\nFiles found:"
 	print "====================\n"
-	t=0
 	if result==[]:
-		print "No results were found"
+	 print "No results were found"
 	else:
-		for x in result:
-			x= re.sub('<li class="first">','',x)
-			x= re.sub('</li>','',x)
-			print x
-			t+=1
-	print "====================\n"
+         print "\n" .join( [ x for x in result ])
+          
 	
 
 if __name__ == "__main__":
-        try: search(sys.argv[1:])
-	except KeyboardInterrupt:
-		print "Search interrupted by user.."
-	except:
-		sys.exit()
+ try:
+  search(sys.argv[1:])
+ except KeyboardInterrupt:
+  print "Search interrupted by user.."
+  sys.exit(1)
+
+        
+
+	
