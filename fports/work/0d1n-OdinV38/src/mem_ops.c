#include "mem_ops.h"



void free_global_buf()
{
	XFREE(blob.buf_list);
	XFREE(blob.buf_payloads);
	XFREE(param.path_output);
	XFREE(param.datatable);
	XFREE(blob.buf_proxy);
	XFREE(blob.buf_useragent);
	XFREE(blob.buf_custom);
}

static void *
xmalloc_fatal(size_t size) 
{

	DEBUG("\n Memory FAILURE...\n size dbg: %lu\n",size);

	exit(0);
}

void *
xmalloc (size_t size) 
{
	void *ptr = malloc (size);

	if (ptr == NULL) 
		return xmalloc_fatal(size);

	return ptr;
}

void *
xcalloc (size_t mem, size_t size) 
{
	void *ptr = calloc (mem, size);

	if (ptr == NULL) 
		return xmalloc_fatal(mem*size);

	return ptr;
}

void *
xrealloc (void *ptr, size_t size) 
{
	void *p = realloc (ptr, size);

	if (p == NULL) 
		return xmalloc_fatal(size);

	return p;
}

void 
xfree(void **ptr) 
{
	assert(ptr);

	if( ptr != NULL )
        {
		free(*ptr);
		*ptr=NULL;	
        }
	
}

size_t 
WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data) 
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = xrealloc(mem->memory, mem->size + realsize + 1);

	if ( mem->memory ) 
	{
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
               
	}

	return realsize;
}


int 
wait_on_socket(curl_socket_t sockfd, int for_recv, long timeout_ms)
{
	struct timeval tv;
	fd_set infd, outfd, errfd;
	int res;

	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec= (timeout_ms % 1000) * 1000;

	FD_ZERO(&infd);
	FD_ZERO(&outfd);
	FD_ZERO(&errfd);

	FD_SET(sockfd, &errfd); 

	if(for_recv)
		FD_SET(sockfd, &infd);
	else
		FD_SET(sockfd, &outfd);
  
	res = select(sockfd + 1, &infd, &outfd, &errfd, &tv);

	return res;
}

void *
xmallocarray (size_t nmemb, size_t size) 
{
	if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) && nmemb > 0 && SIZE_MAX / nmemb < size) 
	{
		DEBUG("integer overflow block");
		exit(0);
	}

	void *ptr = malloc (nmemb*size);

	if (ptr == NULL) 	
		return xmalloc_fatal(size);

	return ptr;
}

// based in OpenBSD reallocarray() function http://man.openbsd.org/reallocarray.3


void *
xreallocarray (void *ptr, size_t nmemb, size_t size) 
{
	if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) && nmemb > 0 && SIZE_MAX / nmemb < size) 
	{
		DEBUG("integer overflow block");
		exit(0);
	}

	void *p = realloc (ptr, nmemb*size);

	if (p == NULL) 	
		return xmalloc_fatal(size);

	return p;
}
