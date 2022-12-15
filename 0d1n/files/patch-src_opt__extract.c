--- src/opt_extract.c.orig	2022-07-10 02:56:04 UTC
+++ src/opt_extract.c
@@ -99,27 +99,27 @@ LAST
  YELLOW
  "Example 1 to find SQL-injection:\n"
 LAST
-"0d1n --host 'http://site.com/view/1^/product/^/' --payloads /opt/0d1n/payloads/sqli_list.txt --find_string_list /opt/0d1n/payloads/sqli_str2find_list.txt --log log1337 --tamper randcase --threads 800 --timeout 3 --save_response\n"
+"0d1n --host 'http://site.com/view/1^/product/^/' --payloads /usr/local/share/0d1n/payloads/sqli_list.txt --find_string_list /usr/local/share/0d1n/payloads/sqli_str2find_list.txt --log log1337 --tamper randcase --threads 800 --timeout 3 --save_response\n"
 "\n"
 YELLOW
  "Example 2 to Bruteforce in simple auth:\n"
 LAST
-"0d1n --host 'http://site.com/auth.py' --post 'user=admin&password=^' --payloads /opt/0d1n/payloads/wordlist.txt --log log007 --threads 500 --timeout 3 --save_response\n"
+"0d1n --host 'http://site.com/auth.py' --post 'user=admin&password=^' --payloads /usr/local/share/0d1n/payloads/wordlist.txt --log log007 --threads 500 --timeout 3 --save_response\n"
 "\n"
 YELLOW
 "Example 3 to search XSS and pass anti-csrf token:\n"
 LAST
-"0d1n --host https://page/test.php --post 'admin=user_name&pass=^' --payloads /opt/0d1n/payloads/xss.txt --find_string_list opt/0d1n/payloads/xss.txt --token_name name_token_field --log logtest --save_response\n"
+"0d1n --host https://page/test.php --post 'admin=user_name&pass=^' --payloads /usr/local/share/0d1n/payloads/xss.txt --find_string_list opt/0d1n/payloads/xss.txt --token_name name_token_field --log logtest --save_response\n"
 "\n"
 YELLOW
 "Example 4 Brute dir:\n"
 LAST
-"0d1n --host https://page/^ --payloads /opt/0d1n/payloads/dir_brute.txt --threads 800 --timeout 3 --log logtest_brutedir --save_response\n"
+"0d1n --host https://page/^ --payloads /usr/local/share/0d1n/payloads/dir_brute.txt --threads 800 --timeout 3 --log logtest_brutedir --save_response\n"
 YELLOW
 "\n"
 "Example 5 Keep alive test like slowloris:\n"
 LAST
-"0d1n --host https://page/ --threads 50 --keep_alive_test --max_requests 1000 --proxy-rand  /opt/0d1n/payloads/proxy.txt --useragent-rand /opt/0d1n/payloads/useragents.txt --log logtest_keepalive --save_response\n"
+"0d1n --host https://page/ --threads 50 --keep_alive_test --max_requests 1000 --proxy-rand  /usr/local/share/0d1n/payloads/proxy.txt --useragent-rand /usr/local/share/0d1n/payloads/useragents.txt --log logtest_keepalive --save_response\n"
 "\nNotes:\n"
 LAST
 "Look the character '^', is lexical char to change to payload list lines...\n"
