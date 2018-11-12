--- inputs.py.orig	2018-11-05 20:44:04 UTC
+++ inputs.py
@@ -20,7 +20,7 @@ No exceptions exported.
 import os
 import hashlib
 import requests
-from outputs import SiteDetailOutput
+from automater.outputs import SiteDetailOutput
 from requests.exceptions import ConnectionError
 from requests.exceptions import HTTPError
 from xml.etree.ElementTree import ElementTree
