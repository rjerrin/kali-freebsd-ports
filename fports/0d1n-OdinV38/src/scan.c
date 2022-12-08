#include "scan.h"


long int keep_alive_test_scan(int threads_total)
{
	long int total_requests= 0;
	threadpool thpool = thpool_init(threads_total);
	int requests_limit = param.max_requests;
	int inter = 0;

	while(requests_limit)
	{
		
		if (total_requests<LONG_MAX)
			total_requests++;

		thpool_add_work(thpool, spider, NULL);

		if(inter == threads_total)
		{
			thpool_wait(thpool);			
			inter = 0;
		}

		total_requests++;
		requests_limit--;
		inter++;
	}

	thpool_destroy(thpool);
	return total_requests;

}


long int parse_n_scan(const char* input, int threads_total)
{
	char *start = NULL, *end = NULL;
	long int total_requests= 0;
	int inter = 0;

	start = end = (char*) input; 
	threadpool thpool = thpool_init(threads_total);

	while( (end = strchr(start, '\n')) )
	{
		
		if (total_requests<LONG_MAX)
			total_requests++;

		thpool_add_work(thpool, spider, (void*)start);

		if(inter == threads_total)
		{
			thpool_wait(thpool);			
			inter = 0;
		}

		inter++;
		start = end + 1;
		total_requests++;
	}


	thpool_destroy(thpool);
	return total_requests;
}

void scan_gcc_old(void)
{
	FILE *fp = NULL;
        long int total_requests = 0;	
	int threadss = 2, timeout = 3;
	char *line = NULL;
	size_t len = 0;

	if (param.threads!=NULL)
		threadss = (int)strtol(param.threads,(char **)NULL,10);

	if (param.timeout!=NULL)
		timeout = (int)strtol(param.timeout,(char **)NULL,10);

	if (timeout<1)
		timeout = 3;

	printf("Threads per request: %d\n Timeout seconds per threads: %d\n",threadss,timeout);
	puts("start...");


	if(param.log!=NULL)
		prepare_datatable();

	threadpool thpool = thpool_init(threadss);


	if(param.keep_alive_test!=true)
	{
		fp = fopen(param.payloads, "r");

 		if (!fp)
		{ 
			DEBUG("error to open Payload list"); 
			exit(0);
		}

		while ( getline(&line,&len,fp) != -1) 
		{
			if (total_requests<LONG_MAX)
				total_requests++;
	
			thpool_add_work(thpool, spider, (void *)line);
	
			thpool_wait(thpool);			

	  	}
	} else {
		int requests_limit = param.max_requests;

		while(requests_limit)
		{
			if (total_requests<LONG_MAX)
				total_requests++;
	
			thpool_add_work(thpool, spider, NULL);
			thpool_wait(thpool);			
			requests_limit--;
		}
	}

	thpool_destroy(thpool);
	threadss = 0;
	puts("Sleep timeout seconds");
	sleep(timeout);

	if(param.log!=NULL)
		end_datatable(param.datatable);

	puts(YELLOW);

	if(param.path_output != NULL)
		fprintf(stdout,"Look the file %s\n Total Requests %ld\n Path table: %s\n",param.path_output, total_requests, param.datatable);

	if(param.log != NULL)
		fprintf(stdout,"\nExecute 0d1n_view server \nFind the file html in https://127.0.0.1:40111/tables/hammer_%s.html\n", param.log);
	

	printf("0d1n done...");

	puts(LAST);

	free_global_buf();

	if (fclose(fp) == EOF)
	{
		DEBUG("Error in close()");
		exit(0);
	}

	fp = NULL;

	exit(0);
}



void scan_gcc_new(void)
{
        long int total_requests = 0;	
	int total_threads = 2, timeout = 3;


	if (param.threads!=NULL)
		total_threads = (int)strtol(param.threads,(char **)NULL,10);

	if (param.timeout!=NULL)
		timeout = (int)strtol(param.timeout,(char **)NULL,10);

	if (timeout<1)
		timeout = 3;

	printf("Threads per request: %d\n Timeout seconds per threads: %d\n",total_threads,timeout);
	puts("start...");

	if(param.log!=NULL)
		prepare_datatable();


	if(param.keep_alive_test!=true)
		total_requests = parse_n_scan(blob.buf_payloads, total_threads);
	else  
		total_requests = keep_alive_test_scan(total_threads);
	
	puts("Sleep timeout seconds");
	sleep(timeout);

	if(param.log!=NULL)
		end_datatable(param.datatable);

	puts(YELLOW);

	if(param.path_output!=NULL)
		fprintf(stdout,"End scan \n look the file %s\n Total Requests %ld\n Path table: %s\n",param.path_output, total_requests, param.datatable);

	if(param.log != NULL)
		fprintf(stdout,"\nExecute 0d1n_view server \nFind the file html in https://127.0.0.1:40111/tables/hammer_%s.html\n", param.log);

	printf("0d1n done...");

	puts(LAST);
	
	free_global_buf();

	exit(0);
}
