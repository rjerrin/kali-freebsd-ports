/*
Author:Antonio Costa aka " Cooler_ "
contact: coolerlair[at]gmail[dot]com


    Copyright (C) 2012 0d1n authors,
    
    This file is part of 0d1n
    
    0d1n is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    0d1n is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.



What this IT ?
this is another Web POST,GET test tool lol

need libcurl to run

$ sudo apt-get install libcurl-dev
if rpm distro
$ sudo yum install libcurl-devel

$ make
$./0d1n


*/
#include "opt_extract.h"



struct choice param;
struct bufferglobal blob;

void init_banner_odin()
{
 puts(
 CYAN
   "       ~.             ~             \n"                      
   "         01...___|__..10.              \n" 
   "          1010   101   101             \n" 
   "           0101  :Bug  :Sec   `.oo'   \n"
   "           :101  |010  |101  ( (`-'   \n"
   " .---.    1010  ;110  ;010   `.`.     \n"
   "/ .-._)  111-\"\"\"|\"\"\"'-000      `.`.   \n"
   "( (`._) .-.  .-. |.-.  .-.  .-. ) ) \n"
   " \\ `---( 1 )( 0 )( 1 )( 1 )( 0 )-' /  \n"
   " `.    `-'  `-'  `-'  `-'  `-'  .'   \n"
   "   `---------------------------'     \n"
 YELLOW
 "0d1n Web Hacking Tool version 3.8\n"
 LAST
 "--host :	Host to scan or  GET method to fuzz  site.com/page.jsp?var=^&var2=^ \n"
 "--post :	POST method fuzz params  ex: 'var=^&x=^...'\n"
 "--cookie :    COOKIE  fuzz params  ex: 'var=^&var2=^...'\n"  
 "--custom :    Load external HTTP Request template file to change points with lexical char '^' to fuzzing \n(note: if you use this argv the payload list need be urlencoded) '\n" 
 "--agent :    UserAgent fuzz  params  ex: 'firefox version ^...'\n"
 "--method :    Change method to Custom http method like DELETE, PUT, TRACE, CONNECT... \n"
 "--header :    Add line on http header \n"
 "--payloads :	Payload list to inject\n"
 "--find_string_list :	Strings list to find on response\n"
 "--find_regex_list :	Regex list to find on response(this regex is posix)\n"
 "--cookie_jar :	 Load cookie jar file\n"
 "--log :	Create text output of result\n"
 "--UserAgent :	Custom UserAgent\n"
 "--CA_certificate :	Load CA certificate to work with SSL\n"
 "--SSL_version :	Choice SSL version by number: \n	1 = SSLv1\n	2 = SSLv2\n	3 = SSLv3\n	4 = TLSv1.0\n	5 = TLSv1.1\n	6 = TLSv1.2\n" // https://curl.haxx.se/libcurl/c/CURLOPT_SSLVERSION.html
 "--threads : Number of threads to use, default is 4, you can choice any number here, try 500, 1000... each machine have a different context.\n"
 "--timeout :	Timeout to wait Response\n"
 "--proxy :   Proxy_address:port to use single proxy tunnel\n	example: format [protocol://][user:password@]machine[:port]\n"
 "--proxy-rand :   First argv is a file list of proxys, proxy list to use random proxy per Request\n	example: format [protocol://][user:password@]machine[:port]\n"
 "--useragent-rand : Need a list of User agents, use different user agent per request\n"
 "--tamper : Payload tamper to try bypass filters\n   Choice one option :\n    encode64 : to encode payload to 64 base \n    randcase : to use lower and upper case random position in string\n"
 "    urlencode :  converts characters into a format that can be transmitted over the Internet, percent encoding\n    double_urlencode : converts payload two times with urlencode\n"
"    spaces2comment:  change spaces ' ' to comment '/**/'\n    unmagicquote: change apostrophe to a multi-byte \%bf\%27 \n"
"    apostrophe2nullencode: change apostrophe to illegal double unicode counterpart\n    rand_comment: to use random comment '/**/' position in payload string\n"
"    rand_space: write random ' ' blank spaces\n    replace_keywords: replace especial words, SELECT to SELselectECT etc...\n"
"--token_name : Name of anti-csrf token field to get and use in your request\n"
YELLOW
YELLOW
 "\nEnable-options-args:\n"
LAST
 "--save_response :   Enable save response highlights view when you click at http status code in datatables \n"
 "--json_headers :   Enable add JSON headers in Request \n"
 "--keep_alive_test : Enable no-cache header + keep alive with rand number to test Denial of Service \n"
 "--max_requests : keep alive test total requests in test \n"
 "--race : Enable a resource to explore race conditions through multithread in sending requests. So the number of requests simultaneously follow the number of threads(input of argument --threads).\n\n"
 YELLOW
 "Example 1 to find SQL-injection:\n"
LAST
"0d1n --host 'http://site.com/view/1^/product/^/' --payloads /opt/0d1n/payloads/sqli_list.txt --find_string_list /opt/0d1n/payloads/sqli_str2find_list.txt --log log1337 --tamper randcase --threads 800 --timeout 3 --save_response\n"
"\n"
YELLOW
 "Example 2 to Bruteforce in simple auth:\n"
LAST
"0d1n --host 'http://site.com/auth.py' --post 'user=admin&password=^' --payloads /opt/0d1n/payloads/wordlist.txt --log log007 --threads 500 --timeout 3 --save_response\n"
"\n"
YELLOW
"Example 3 to search XSS and pass anti-csrf token:\n"
LAST
"0d1n --host https://page/test.php --post 'admin=user_name&pass=^' --payloads /opt/0d1n/payloads/xss.txt --find_string_list opt/0d1n/payloads/xss.txt --token_name name_token_field --log logtest --save_response\n"
"\n"
YELLOW
"Example 4 Brute dir:\n"
LAST
"0d1n --host https://page/^ --payloads /opt/0d1n/payloads/dir_brute.txt --threads 800 --timeout 3 --log logtest_brutedir --save_response\n"
YELLOW
"\n"
"Example 5 Keep alive test like slowloris:\n"
LAST
"0d1n --host https://page/ --threads 50 --keep_alive_test --max_requests 1000 --proxy-rand  /opt/0d1n/payloads/proxy.txt --useragent-rand /opt/0d1n/payloads/useragents.txt --log logtest_keepalive --save_response\n"
"\nNotes:\n"
LAST
"Look the character '^', is lexical char to change to payload list lines...\n"
CYAN
 "Coded by Cooler_\n coolerlair[at]gmail[dot]com\n "
 );
 puts(LAST);
}



void
load_files()
{	
	if(param.keep_alive_test != true)	
		blob.buf_payloads = read_lines(param.payloads);
	
	if(param.custom != NULL)	
		blob.buf_custom = read_lines(param.custom);
	
	if(param.proxy_rand != NULL)
	{	
		printf("Load proxy list: %s",param.proxy_rand);	
		blob.buf_proxy = read_lines(param.proxy_rand);
		blob.proxy_lines = char_type_counter( blob.buf_proxy,'\n' );
	}

	if(param.useragent_rand != NULL)
	{	
		blob.buf_useragent = read_lines(param.useragent_rand);
		blob.useragent_lines = char_type_counter( blob.buf_useragent,'\n');
	}

	if (param.find_string_list!=NULL)
		blob.buf_list = read_lines(param.find_string_list);

	if (param.find_regex_list!=NULL && blob.buf_list == NULL)
		blob.buf_list = read_lines(param.find_regex_list);
}

void 
parser_opts (int argc, char **argv)
{

	char c;

	static struct option long_options[] =
	{
		{"host", required_argument, NULL, 'h'},
		{"payloads", required_argument, NULL, 'p'},	
		{"custom", required_argument, NULL, 'e'},
		{"find_string_list", required_argument, NULL, 'f'},
		{"find_regex_list", required_argument, NULL, 'z'},
		{"cookie_jar", required_argument, NULL, 'c'},
		{"cookie", required_argument, NULL, 'i'},
		{"agent", required_argument, NULL, 'a'},
		{"post", required_argument, NULL, 'P'},
		{"method", required_argument, NULL, 'b'},
		{"header", required_argument, NULL, 'd'},
		{"log", required_argument, NULL, 'o'},
		{"UserAgent", required_argument, NULL, 'u'},
		{"CA_certificate", required_argument, NULL, 's'},
		{"SSL_version", required_argument, NULL, 'V'},
		{"threads", required_argument, NULL, 't'},
 		{"timeout", required_argument, NULL, 'T'}, 
 		{"proxy", required_argument, NULL, '1'}, 
 		{"proxy-rand", required_argument, NULL, '2'},
 		{"useragent-rand", required_argument, NULL, '7'},
 		{"tamper", required_argument, NULL, 'w'}, 
		{"save_response", no_argument, 0, 'k'},	
		{"json_headers", no_argument, 0, 'j'},
		{"keep_alive_test", no_argument, 0, '5'},
 		{"max_requests", required_argument, NULL, '6'},
 		{"token_name", required_argument, NULL, '4'},
		{"race", no_argument, 0, 'r'},
		{NULL, 0, NULL, 0}
	};
	

	if (argc < 7) 
	{
		init_banner_odin();
		DEBUG(" Need more arguments.\n");
		exit(0);
	}
 

 	opterr = 0;
	param.max_requests = 0;
	param.keep_alive_test = false;
	param.save_response = false;
	param.race_test = false;
	param.json_headers = false;

 	while ((c = getopt_long(argc, argv, "h:p:f:z:e:c:i:a:P:b:d:o:u:s:t:T:1:2:w:k:j:V:3:4:5:6:7:r",long_options,NULL)) != -1)
  		switch(c) 
  		{
// Host
   			case 'h':
    				
				if ( strnlen(optarg,256)<= 128 )
				{
    					param.host = optarg;
// todo improve that function
//					validate_hostname(pack[0]);
    					printf("Host: %s \n", param.host);
    					
				} else {
					DEBUG("Error \nArgument Host is very large \n");
					exit(0);
				}
				break;
// payload list
			case 'p':
				if ( strnlen(optarg,256)<= 128 )
				{
    					param.payloads = optarg;
    					printf("Payloads: %s \n",param.payloads);
    					
				} else {
					DEBUG("Error \nArgument Payloads is very large  \n");
					exit(0);
				}
				break;

// custom http request file
			case 'e':
				if ( strnlen(optarg,256)<= 128 )
				{
    					param.custom = optarg;
    					printf("Custom HTTP Request: %s \n",param.custom);
    					
				} else {
					DEBUG("Error \nArgument custom is very large  \n");
					exit(0);
				}
				break;

   			case 'f':    				
				if ( strnlen(optarg,256)<= 128 )
				{
    					param.find_string_list = optarg;
    					printf("Find list: %s \n", param.find_string_list);
    				} else {
			
					DEBUG("Error \nArgument Find list file is very large  \n");
					exit(0);
				}
				break;

   			case 'z':			
				if ( strnlen(optarg,256)<= 128 )
				{
    					param.find_regex_list = optarg;
    					printf("Regex list: %s \n",param.find_regex_list);
    				} else {
					DEBUG("Error \nArgument Regex file is very large  \n");
					exit(0);
				}
				break;

   			case 'c':
				if ( strnlen(optarg,256)<= 64 )
				{
    					param.cookie_jar = optarg;
				} else {

					DEBUG("Error \nArgument cookie jar file is very large  \n");
					exit(0);
				}
    				break;

   			case 'a':
				if ( strnlen(optarg,256)<= 64 )
				{
    					param.agent = optarg;
				} else {

					DEBUG("Error \nArgument Useragent fuzz is very large  \n");
					exit(0);
				
				}
    				break;


   			case 'i':
				if ( strnlen(optarg,256)<= 64 )
				{
    					param.cookie = optarg;
				} else {

					DEBUG("Error \nArgument cookie is very large  \n");
					exit(0);
				}
    				break;

   			case 'P':
				if ( strnlen(optarg,512)<= 256 )
				{
    					param.post = optarg;
				} else {
					DEBUG("Error \nArgument POST is very large  \n");
					exit(0);
				}
    				break;

   			case 'b':
				if ( strnlen(optarg,14)<= 12 )
				{
    					param.method = optarg;
				} else {
					DEBUG("Error \nArgument method is very large  \n");
					exit(0);
				}
    				break;

   			case 'd':
				if ( strnlen(optarg,129)<= 128 )
				{
    					param.header = optarg;
				} else {
					DEBUG("Error \nArgument header is very large  \n");
					exit(0);
				}
    				break;

   			case 'o':
				if ( strnlen(optarg,256)<= 128 )
				{
    					param.log = optarg;
    					printf("Log file: %s \n", param.log);
    				} else {
					DEBUG("Error \nArgument Log file is very large \n");
					exit(0);
				}
				break;
   
   			case 'u':
				if ( strnlen(optarg,256)<= 128 )
				{
    					param.UserAgent = optarg;
    				} else {	
					DEBUG("Error \nArgument user agent is very large  \n");
					exit(0);
				}
				break;
 
   			case 's':
				if ( strnlen(optarg,256)<= 128 )
				{
    					param.CA_certificate = optarg;
				} else {	
					DEBUG("Error \nArgument ca cert file name is very large  \n");
					exit(0);
				}
				break;

 
   			case 't':
				if ( strnlen(optarg,7)<= 6 )
				{
    					param.threads = optarg;
				} else {	
					DEBUG("Error \nArgument threads is very large  \n");
					exit(0);
				}
				break;
 
   			case 'T':
				if ( strnlen(optarg,4)<= 3 )
				{	
    					param.timeout = optarg;
				} else {	
					DEBUG("Error \nArgument timeout is very large need 3 digit  \n");
					exit(0);
				}
				break;

// proxy single
   			case '1':
				if ( strnlen(optarg,47)<= 48 )
				{	
    					param.proxy = optarg;
				} else {	
					DEBUG("Error \nArgument proxy is very large \n");
					exit(0);
				}
				break;
//proxy list
   			case '2':
				if ( strnlen(optarg,63)<= 256 )
				{	
    					param.proxy_rand = optarg;
				} else {	
					DEBUG("Error \nArgument proxy list is very large \n");
					exit(0);
				}
				break;

// user agent list to use rand useragen per request
   			case '7':
				if ( strnlen(optarg,63)<= 256 )
				{	
    					param.useragent_rand = optarg;
				} else {	
					DEBUG("Error \nArgument useragent list is very large \n");
					exit(0);
				}
				break;

// tamper
   			case 'w':
				if ( strnlen(optarg,18)<= 17 )
				{	
    					param.tamper = optarg;
				} else {	
					DEBUG("Error \nArgument tamper is very large \n");
					exit(0);
				}
				break;


 // save response
   			case 'k':
    				param.save_response = true;
				break;
 // explore race condition	
   			case 'r':
    				param.race_test = true;
				break;
		
   			case 'j':
    				param.json_headers = true;
				break;
 			
 				
   			case 'V':
				if ( strnlen(optarg,4)<= 1 )
				{	
    					param.SSL_version = optarg;
				} else {	
					DEBUG("Error \nArgument SSL version one digit example 1,2,3,32,39 : \n1 is TLSv1\n2 is SSLv2\n3 is SSLv3\n5 is TLS 1.1\n6 is TLS 1.2\n7 is TLS 1.3\n 0 default if possible use last version\n");
					exit(0);
				}
				break;


			case '6':
				if ( strnlen(optarg,8)<= 9 )
				{
    					param.max_requests = (int)strtol(optarg,NULL,10);
    					printf("Max requests : %d \n", param.max_requests);
    					
				} else {
					DEBUG("Error \nArgument max requests is very large  \n");
					exit(0);
				}
				break;


			case '4':
				if ( strnlen(optarg,256)<= 128 )
				{
    					param.token_name = optarg;
    					printf("Token name to get : %s \n", param.token_name);
    					
				} else {
					DEBUG("Error \nArgument token name is large  \n");
					exit(0);
				}
				break;


			case '5':
    				param.keep_alive_test = true;
				break;



   			case '?':
    				if(optopt == 'h' || optopt == 'p' || optopt == 'f' || optopt == 'c' || optopt == 'P' || optopt == 'o' || optopt=='s' || optopt == '6' || optopt == '7') 
    				{
     					init_banner_odin();
     					puts(RED);
     					DEBUG("Option -%c requires an argument.\n", optopt); 
     					puts(LAST);
     					exit(0);
    				}
				break;

			default:
				init_banner_odin();
				DEBUG("error argv, need more arguments.\n");
				exit(0);
  		}

	if(param.log==NULL && (param.max_requests == 0 || param.save_response==true)  )
	{
		DEBUG("To run need a argument log");
		exit(0);
 	}


	if(param.payloads==NULL && param.max_requests == 0)
	{
		DEBUG("To run, need a argument payload");
		exit(0);
 	}

	load_files();
}

