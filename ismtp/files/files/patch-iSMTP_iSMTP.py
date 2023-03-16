--- iSMTP/iSMTP.py.orig	2023-03-16 12:18:51 UTC
+++ iSMTP/iSMTP.py
@@ -35,7 +35,7 @@ split_target = "\n " + colors.white + "=" * 23 + " sta
 
 def help():
 	print(banner)
-	print(" Usage: ./iSMTP.py <OPTIONS>\n")
+	print(" Usage: ismtp <OPTIONS>\n")
 	print(colors.red + " Required:\n" + colors.normal)
 	print("\t-f <import file>\tImports a list of SMTP servers for testing.\n\t\t\t\t(Cannot use with '-h'.)")
 	print("\t-h <host>\t\tThe target IP and port (IP:port).\n\t\t\t\t(Cannot use with '-f'.)")
