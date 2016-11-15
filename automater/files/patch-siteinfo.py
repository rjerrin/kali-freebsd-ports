--- siteinfo.py.orig	2016-05-30 22:54:57 UTC
+++ siteinfo.py
@@ -29,6 +29,8 @@ import requests
 import re
 import time
 import os
+import sys
+sys.path.append('/usr/local/lib/python2.7/site-packages/automater')
 from os import listdir
 from os.path import isfile, join
 from requests.exceptions import ConnectionError
@@ -38,8 +40,8 @@ from utilities import VersionChecker
 
 requests.packages.urllib3.disable_warnings()
 
-__TEKDEFENSEXML__ = 'tekdefense.xml'
-__SITESXML__ = 'sites.xml'
+__TEKDEFENSEXML__ = '/usr/local/share/automater/tekdefense.xml'
+__SITESXML__ = '/usr/local/share/automater/sites.xml'
 
 class SiteFacade(object):
     """
