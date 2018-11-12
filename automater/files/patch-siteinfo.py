--- siteinfo.py.orig	2018-11-05 20:43:56 UTC
+++ siteinfo.py
@@ -32,9 +32,9 @@ import os
 from os import listdir
 from os.path import isfile, join
 from requests.exceptions import ConnectionError
-from outputs import SiteDetailOutput
-from inputs import SitesFile
-from utilities import VersionChecker
+from automater.outputs import SiteDetailOutput
+from automater.inputs  import SitesFile
+from automater.utilities import VersionChecker
 
 requests.packages.urllib3.disable_warnings()
 
