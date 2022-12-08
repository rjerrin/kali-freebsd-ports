#include "spider.h"


struct curl_slist *keep_alive_generate(struct curl_slist *headers)
{
	curl_slist_append(headers, "Cache-Control: noCache");
	curl_slist_append(headers, "Connection: keep-alive");

	char keep_value[]="Keep-Alive: ";
	char num_keep[8];
	char header_keep_custom[32];

	// keep-Alive: random_number(four numbers 0-9)
	memset(num_keep,0,7);
	rand_number(num_keep,4);
	memset(header_keep_custom,0,31); // if use 20 crash because hardening use canary cookie in last chunk
	snprintf(header_keep_custom,31,"%s%s",keep_value,num_keep);

	curl_slist_append(headers, header_keep_custom);

	return headers;
}

// pthread_mutex_t mutex_spider = PTHREAD_MUTEX_INITIALIZER;

void spider(void *in)
{
//	pthread_mutex_lock(&mutex_spider);
	curl_off_t time_total = 0;
	long status = 0,length = 0;
	int res = 0, try = 1, POST = 0, timeout = 3, debug_host = 3; 
	char *lines=in==NULL?" ":(char *)in;
	char *make = NULL, *make2 = NULL, *make_cookie = NULL, *make_agent = NULL;
	char *token = NULL, *request_file = NULL;
	char time_total_str[35];
	struct curl_slist *headers = NULL;
	struct MemoryStruct chunk;

	memset(time_total_str,0,34);

	if (param.timeout!=NULL)
		timeout = (int)strtol(param.timeout,(char **)NULL,10);

// if need get anti-csrf token
	if(param.host!=NULL && param.token_name!=NULL)
	{
		token = xmalloc(sizeof(char)*2048); 
		memset(token,0,2047); // note: last byte for canary, hardening makefile...
		token = get_anti_csrf_token(param.host,param.token_name);
	}



// payload tamper, get payload of lines and make tamper 
	if(param.tamper!=NULL)
		lines = tamper_choice(param.tamper,lines);

	if(lines != NULL)
		chomp(lines);

// goto to fix signal stop if user do ctrl+c
	try_again:


	POST=param.post?1:0;

	while(try)
	{
		CURL *curl;  
//		curl_global_init(CURL_GLOBAL_ALL); 

		chunk.memory = NULL; 
		chunk.size = 0;  

		curl_socket_t sockfd; /* socket */
		long sockextr;
		size_t iolen;


		curl = curl_easy_init();
		
// add payload at inputs
		if(param.custom==NULL) //if custom request  argv mode null
		{
			make2 = replace ( (POST?param.post:param.host),"^",lines);

			if (token)
		 		make = insert_csrf_token(make2, param.token_name, token); 
			else
				make = xstrndup(make2, strlen(make2));	

			if (param.cookie!=NULL)	
				make_cookie = replace( param.cookie,"^",lines);	
	
			if (param.UserAgent!=NULL)
				make_agent = replace( param.UserAgent,"^",lines);

			curl_easy_setopt(curl,  CURLOPT_URL, param.host);
		} else {
// if is custom request
			request_file = blob.buf_custom;
			make2 = replace( request_file,"^",lines);	
			curl_easy_setopt(curl,  CURLOPT_URL, param.host);

			if (token!=NULL)
				make = insert_csrf_token(make2, param.token_name, token);

			else
				make = xstrndup(make2, strlen(make2));

			XFREE(request_file);
		}	
 
		if ( POST )
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, make);
      
		curl_easy_setopt(curl,  CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl,  CURLOPT_WRITEDATA, (void *)&chunk);

// load user agent     
		if ( param.agent!=NULL )
		{
			curl_easy_setopt(curl,  CURLOPT_USERAGENT, param.agent);
		} else {
			if(param.useragent_rand==NULL)
				curl_easy_setopt(curl,  CURLOPT_USERAGENT, "Mozilla/5.0 (0d1n v0.1) ");
			else
				curl_easy_setopt(curl,  CURLOPT_USERAGENT, random_line_of_buffer( blob.buf_useragent, blob.useragent_lines));
		}



// encode

		curl_easy_setopt(curl,  CURLOPT_ENCODING,"gzip,deflate");

// keep-alive denial of service test, based in old tools like slowloris and goldeneye tool

		if(param.keep_alive_test==true)
		{

				headers=keep_alive_generate(headers);
				curl_easy_setopt(curl,  CURLOPT_HTTPHEADER, headers);
				curl_slist_free_all(headers);
		} 

		

// json headers to use JSON

		if (param.header!=NULL)
		{
			curl_slist_append(headers, param.header);

			if (param.json_headers==true)
			{
				curl_slist_append(headers, "Accept: application/json");
				curl_slist_append(headers, "Content-Type: application/json");
			}

			curl_easy_setopt(curl,  CURLOPT_HTTPHEADER, headers);
			curl_slist_free_all(headers);

		} else {

			if (param.json_headers==true)
			{

				curl_slist_append(headers, "Accept: application/json");
				curl_slist_append(headers, "Content-Type: application/json");
				curl_easy_setopt(curl,  CURLOPT_HTTPHEADER, headers);
				curl_slist_free_all(headers);
			}

		}




//use custom method PUT,DELETE...
		if (param.method!=NULL)
			curl_easy_setopt(curl,  CURLOPT_CUSTOMREQUEST, param.method);

// load cookie jar
		if (param.cookie_jar != NULL)
		{
			curl_easy_setopt(curl,CURLOPT_COOKIEFILE,param.cookie_jar);
			curl_easy_setopt(curl,CURLOPT_COOKIEJAR,param.cookie_jar);
		} else {
			if(param.keep_alive_test!=true)
				curl_easy_setopt(curl,CURLOPT_COOKIEJAR,"odin_cookiejar.txt");
		}
// LOAD cookie fuzz

		if (param.cookie!=NULL)
			curl_easy_setopt(curl,CURLOPT_COOKIE,make_cookie);


// LOAD UserAgent FUZZ
		if (param.UserAgent!=NULL)
			curl_easy_setopt(curl,CURLOPT_USERAGENT,make_agent);


		curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1);
// Load cacert
		if (param.CA_certificate != NULL) 
		{
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2);
			curl_easy_setopt(curl, CURLOPT_CAINFO, param.CA_certificate);
		} else {

			curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,0L); 
			curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST,0L); 
		}

		if (timeout) 
			curl_easy_setopt(curl,CURLOPT_TIMEOUT,timeout); 

// load single proxy
		if (param.proxy != NULL)
		{
			curl_easy_setopt(curl, CURLOPT_PROXY, param.proxy);
	//		curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1);
		}

// load random proxy in list 
		if (param.proxy_rand != NULL)
		{
			curl_easy_setopt(curl, CURLOPT_PROXY, random_line_of_buffer( blob.buf_proxy, blob.proxy_lines) );
	//		curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1);
		}

// choice SSL version
		if ( param.SSL_version != NULL ) 
			curl_easy_setopt(curl,CURLOPT_SSLVERSION,(int)strtol(param.SSL_version,(char **)NULL,10));

		curl_easy_setopt(curl,CURLOPT_VERBOSE,0); 
		curl_easy_setopt(curl,CURLOPT_HEADER,1);  
		
// if use custom request
		if (param.custom!=NULL)
			curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);


// this code chunk purpose,is for not send requests at the same time (load balancer and WAF can detect and block)
// This is for bypass time based request detection in WAFs or load balancers
		if(param.race_test==false)
		{
			usleep(rand()%1000); 
			usleep(rand()%1000); 
			short position_t = rand()%15;
			// you can calibrate this point array
			short array_time[] = { 690, 435, 2915, 1720, 1050, 1600, 200, 800, 500 , 600, 700, 380, 455, 755, 930, 1100 };
			usleep( array_time[position_t]  ); // random microsend wait each request
		}

// custom http request
		if (param.custom!=NULL)
		{
			curl_easy_getinfo(curl, CURLINFO_LASTSOCKET, &sockextr); 
			sockfd = sockextr;

			if (!wait_on_socket(sockfd, 0, 60000L))
				DEBUG("error in socket at custom http request");
			
			res = curl_easy_send(curl, make, strlen(make), &iolen);
// recv data of custom request
			while (1)
			{
				wait_on_socket(sockfd, 1, 60000L);
				chunk.memory = xmallocarray(3024,sizeof(char)); 
				res = curl_easy_recv(curl, chunk.memory, 3023, &iolen); 
				chunk.size = strnlen(chunk.memory,3023);				

				if (strnlen(chunk.memory,3023) > 8)
					break;

			        if (CURLE_OK != res)
        				break;

			}

			
			status = (long)parse_http_status(chunk.memory);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &time_total);

		} else {

			res = curl_easy_perform(curl);
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE,&status);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &time_total);
		}


			

// length of response
		if (chunk.size<=0)
			length=0.0;
		else
			length=chunk.size;

// if have error at status
	
		if (status==0)
		{	
			debug_host--;
			DEBUG("Problem in Host: \n %s\n Host is down ? %s\n", param.host, strerror(errno));
 			DEBUG("curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
			if (debug_host==0 && param.max_requests == 0)
				exit(0);

			sleep(3);

			goto try_again;
			
		
		}

		// https://curl.se/libcurl/c/CURLINFO_TOTAL_TIME_T.html
		snprintf(time_total_str,34,"%.06ld",(long)(time_total % 1000000));


		debug_host=3;
		try--;


		curl_easy_cleanup(curl);
	}
	// Write results in log and htmnl+js in /opt/0d1n/view
	if(param.log)
	{	
		write_result(	(char *)chunk.memory,
			param.datatable,
			lines,
			make,
			make_agent,
			make_cookie,
			status,
			length,
			time_total_str
		);	
	}

	// clear all
	XFREE(chunk.memory);
	XFREE(make_agent);
	XFREE(make_cookie);
	XFREE(make);
	XFREE(make2);

	if(param.tamper != NULL)
		XFREE(lines);

	if(param.token_name != NULL)
		XFREE(token);


//	pthread_mutex_unlock(&mutex_spider);
}

