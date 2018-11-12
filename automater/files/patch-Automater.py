--- Automater.py.orig	2018-11-05 13:59:04 UTC
+++ Automater.py
@@ -37,10 +37,10 @@ No exceptions exported.
 """
 
 import sys
-from siteinfo import SiteFacade, Site
-from utilities import Parser, IPWrapper
-from outputs import SiteDetailOutput
-from inputs import TargetFile
+from automater.siteinfo import SiteFacade, Site
+from automater.utilities import Parser, IPWrapper
+from automater.outputs import SiteDetailOutput
+from automater.inputs import TargetFile
 
 __VERSION__ = '0.21'
 __GITLOCATION__ = 'https://github.com/1aN0rmus/TekDefense-Automater'
