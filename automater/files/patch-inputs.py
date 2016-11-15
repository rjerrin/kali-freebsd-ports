--- inputs.py.orig	2016-05-30 22:54:57 UTC
+++ inputs.py
@@ -20,13 +20,15 @@ No exceptions exported.
 import os
 import hashlib
 import requests
+import sys
+sys.path.append('/usr/local/lib/python2.7/site-packages/automater')
 from outputs import SiteDetailOutput
 from requests.exceptions import ConnectionError
 from requests.exceptions import HTTPError
 from xml.etree.ElementTree import ElementTree
 
 __REMOTE_TEKD_XML_LOCATION__ = 'https://raw.githubusercontent.com/1aN0rmus/TekDefense-Automater/master/tekdefense.xml'
-__TEKDEFENSEXML__ = 'tekdefense.xml'
+__TEKDEFENSEXML__ = '/usr/local/share/automater/tekdefense.xml'
 
 class TargetFile(object):
     """
