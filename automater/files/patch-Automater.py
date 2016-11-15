--- Automater.py.orig	2016-11-15 17:40:09 UTC
+++ Automater.py
@@ -37,6 +37,7 @@ No exceptions exported.
 """
 
 import sys
+sys.path.append('/usr/local/lib/python2.7/site-packages/automater')
 from siteinfo import SiteFacade, Site
 from utilities import Parser, IPWrapper
 from outputs import SiteDetailOutput
