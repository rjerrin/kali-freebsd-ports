#include "get_csrf_token.h"


char *insert_csrf_token(char *payload, char *token_name, char *token)
{
	size_t len_payload = strlen(payload);
	size_t len_token = strlen(token);
	size_t len_token_name = strlen(token_name);
	size_t total = len_payload + len_token + len_token_name +4;
	char *new_payload = xmalloc(sizeof(char)*(total));
	
	memset(new_payload,0,total-1);  

	snprintf(new_payload,total-1,"%s&%s=%s",payload,token_name,token);

	return new_payload;
}

char *
parse_token(char *str)
{
	int x = 0;
	char *parse = xmalloc(sizeof(char)*2048);	
    	memset(parse,0,2047); // i dont use last byte because crash my compiler, hardening use last byte to canary
	
		while ((*str!='"') && (*str!='\'') && (*str!='\n')&&(*str!='\0')&&(x <= 2047))
		{
			parse[x]=*str;
			str++;
			x++;
		}

	if(parse)
		return parse;
	else
		return " ";

}


char *prepare_url(char * url)
{
	short counter=0, max_cmp = 0, x = 0;
	size_t len = strlen(url);
	char *new_url = xmalloc(sizeof(char)*len);	
    	memset(new_url,0,len-1); // i dont use last byte because crash my compiler, hardening use last byte to canary
	max_cmp = char_type_counter(url,'/')-1;

	while ((*url!='\0') && (counter <= max_cmp) && (x <= (short)len-1) )
	{
		if(*url=='/')
			counter++;
		new_url[x]=*url;
		x++;
		url++;
	}

	return new_url;
}

/*

THis function get token, to use custom request to bypass anti csrf 

*/
char *
get_anti_csrf_token(char *url,char *token_name)
{
	CURL *curl;
	CURLcode res;

	struct MemoryStruct chunk;
	char *parse = xmalloc(sizeof(char)*2048);
	bool ValidToken = false;
	char *new_url=NULL;


	if(param.post || param.custom)
		new_url = xstrndup(url,strnlen(url,2048));
	else
		new_url = prepare_url(url);

	chunk.memory = xmalloc(1);  
  	chunk.size = 0;    

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, new_url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

// load user agent     
	if (param.agent!=NULL)
		curl_easy_setopt(curl,  CURLOPT_USERAGENT, param.agent);
	else 
		curl_easy_setopt(curl,  CURLOPT_USERAGENT, "Mozilla/5.0 (0d1n v0.1) ");
	
// load cookie jar
	if (param.cookie_jar != NULL)
	{
		curl_easy_setopt(curl,CURLOPT_COOKIEFILE,param.cookie_jar);
		curl_easy_setopt(curl,CURLOPT_COOKIEJAR,param.cookie_jar);
	} else 
		curl_easy_setopt(curl,CURLOPT_COOKIEJAR,"odin_cookiejar.txt");
	
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

// load single proxy
	if (param.proxy != NULL)
		curl_easy_setopt(curl, CURLOPT_PROXY, param.proxy);

// load random proxy in list 
	if (param.proxy_rand != NULL)
	{
		char *randproxy = Random_linefile(param.proxy_rand);
		curl_easy_setopt(curl, CURLOPT_PROXY, randproxy);
	}

// choice SSL version
	if ( param.SSL_version != NULL ) 
		curl_easy_setopt(curl,CURLOPT_SSLVERSION,(int)strtol(param.SSL_version,(char **)NULL,10));

	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1 );
	curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST,0); 
	curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,0);
 
	res = curl_easy_perform(curl);

	if(res != CURLE_OK) 
	{
 		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
 	} else {
    	
		memset(parse,0,2047);
		short len_max = 0;
		char *line = strtok(chunk.memory, "\n");

		while (line!=NULL)
		{
// read line per line
			if (strstr(line,token_name))
			{
				char *ptr = line;
				deadspace(ptr);	

					while (*ptr!='\n' && *ptr!='\0' && ValidToken==false && len_max <= 2047)
					{
						if (ptr[0]=='v' && ptr[1]=='a' && ptr[2]=='l' && ptr[3]=='u' && ptr[4]=='e')
						{
							ptr += 7;
							ValidToken = true;
							parse=parse_token(ptr);
							len_max++;
								
						}
						ptr++;
					
					}	
			}

			line = strtok(NULL, "\n");
		}	
	

  	}

  	curl_easy_cleanup(curl);
  	free(chunk.memory);
	free(new_url);
  	curl_global_cleanup();

  	if (parse)
  		return parse;
 	else
		return "error";
}

