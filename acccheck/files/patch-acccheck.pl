--- acccheck.pl.orig	2016-03-31 19:53:48 UTC
+++ acccheck.pl
@@ -52,7 +52,7 @@
 
 ###############################################################################
 #Usage:                                                                       #
-#       ./acccheck.pl [optional]                                              #
+#       acccheck [optional]                                                   #
 #                                                                             #
 #                  -t <single target ip>                                      #
 #                       OR                                                    #
@@ -64,13 +64,13 @@
 #                  -U <file containing usernames>                             #
 #                  -v <verbose mode>                                          #
 #Examples:                                                                    #
-#       acccheck.pl -t 10.10.10.1                                             #
+#       acccheck   -t 10.10.10.1                                              #
 #                  This will attempt a BLANK password against the             #
 #                  Administrator account.                                     #
-#       acccheck.pl -t 10.10.10.1 -p password.txt                             #
+#       acccheck   -t 10.10.10.1 -p password.txt                              #
 #                  This will attempt all password in 'password.txt' against   #
 #                  the 'administrator' account.                               #
-#       acccehck.pl -t 10.10.10.1 -u users.txt -p password.txt                #
+#       acccheck    -t 10.10.10.1 -u users.txt -p password.txt                #
 #                  This will attempt all of the passwords in 'password.txt'   #
 #                  against the users in 'users.txt'.                          #
 ###############################################################################
@@ -167,12 +167,12 @@ $verbose=0;
 		
 #show usage information and quit
 sub usage {
-	print color("green"), "\nacccheck.pl v0.2.1 - By Faiz\n\n";
+	print color("green"), "\nacccheck v0.2.1 - By Faiz\n\n";
 	print "Description:\n";
 	print "Attempts to connect to the IPC\$ and ADMIN\$ shares depending on which flags have been\n";
 	print "chosen, and tries a combination of usernames and passwords in the hope to identify\n";
 	print "the password to a given account via a dictionary password guessing attack.\n", color("reset");
-        print "\nUsage = ./acccheck.pl [optional]\n\n";
+        print "\nUsage = acccheck [optional]\n\n";
 	print " -t [single host IP address]\n";
 	print " OR \n";
         print " -T [file containing target ip address(es)]\n";
@@ -185,13 +185,13 @@ sub usage {
 	print " -v [verbose mode]\n\n";
 	print color("green"), "Examples\n";
 	print "Attempt the 'Administrator' account with a [BLANK] password.\n";
-	print "	acccheck.pl -t 10.10.10.1\n";
+	print "	acccheck -t 10.10.10.1\n";
 	print "Attempt all passwords in 'password.txt' against the 'Administrator' account.\n";
-	print "	acccheck.pl -t 10.10.10.1 -P password.txt\n";
+	print "	acccheck -t 10.10.10.1 -P password.txt\n";
 	print "Attempt all password in 'password.txt' against all users in 'users.txt'.\n";
-	print "	acccehck.pl -t 10.10.10.1 -U users.txt -P password.txt\n";
+	print "	acccehck -t 10.10.10.1 -U users.txt -P password.txt\n";
 	print "Attempt a single password against a single user.\n";
-	print "	acccheck.pl -t 10.10.10.1 -u administrator -p password\n", color("reset");
+	print "	acccheck -t 10.10.10.1 -u administrator -p password\n", color("reset");
         exit();
 }
 
