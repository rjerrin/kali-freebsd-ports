--- main.c.orig	2016-11-21 10:33:31 UTC
+++ main.c
@@ -152,7 +152,7 @@ int main( int argc, char *argv[] ) {
 
 	if(verbosity) printf( "Target Aquired: %s\n", target );
 	if(verbosity>=2) printf( "Save Interval: %d attempts\n", save_interval );
-	if(verbosity>=2) printf( "Using Charmap (%d characters):\n  \"%s\"\n", strlen(charmap) - 1, charmap );
+	if(verbosity>=2) printf( "Using Charmap (%ld characters):\n  \"%s\"\n", strlen(charmap) - 1, charmap );
 
 	/* Build result filename */
 	resultfile = malloc(strlen(target)+8);
