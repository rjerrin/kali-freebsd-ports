#include "string_ops.h"
#include "mem_ops.h"
#include "strsec.h"

void 
deadspace(char *str)
{
    char *p = str;
    do *(*p == ' ' ? str : str++) = *p;
    while (*p++);
}




char * 
random_line_of_buffer(char *list, int lines_total)
{
	
	int line_counter = 0, rand_line = 0;
	char *token = strtok(list, "\n");

	entropy_clock();
	rand_line = rand() % lines_total;

     	while (token != NULL)
	{
		if(rand_line == line_counter)
			return token;  
		line_counter++;
		token = strtok(NULL, "\n");
	}
// todo add integer overflow checker

	return token;
}



int 
total_lines_of_buffer(char *list)
{
	
	int line_counter = 0;
	char *start = strtok(list, "\n");


     	while (start != NULL)
	{
		line_counter++;	
		start = strtok(NULL, "\n");
	}
// todo add integer overflow checker

	return line_counter;
}


void *
entropy_clock(void)
{
	double cpu_time;
	struct timeval tv;

	cpu_time = ((double) clock()) / CLOCKS_PER_SEC;
	gettimeofday(&tv, NULL);
	srandom((getpid() << 16) ^ tv.tv_sec ^ tv.tv_usec ^ (int)cpu_time);
  	return NULL;	
}



char *
rand_number(char *dst, int size)
{
	static const char text[] =	"0123456789";                    
	entropy_clock();

	int i, len = random() % (size - 1);
  
	if( !len ) 
		len=8;
 
	for ( i=0; i<len; ++i )
		dst[i] = text[random() % (sizeof text - 1)];

   	dst[i] = '\0';


	entropy_clock();


	return dst;
}

char *
rand_str(char *dst, int size)
{
	static const char text[] =	"abcdefghijklmnopqrstuvwxyz"                     
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	entropy_clock();

	int i, len = random() % (size - 1);
  
	if( !len ) 
		len=8;
 
	for ( i=0; i<len; ++i )
		dst[i] = text[random() % (sizeof text - 1)];

   	dst[i] = '\0';


	entropy_clock();


	return dst;
}

int 
char_type_counter(char *string,char type)
{
	int counter = 0;
 
	while(*string != '\0')
	{
		if(*string==type) 
			counter++;
		string++;
	}
  
	return counter;
}


void 
chomp(char * str)
{
 
	while (*str) 
	{
		if ( *str == '\n' || *str == '\r' ) 
		{
			*str = 0;
			return;
		}
		str++;
	}
  
}

char *
payload_injector(char * ptr,char * payload,int counter)
{
	size_t len_ptr = strlen(ptr), len_payload = strlen(payload), total_len = len_ptr+(len_payload* counter);
	char *new = xmallocarray((total_len+1),sizeof(char));
	short i = 0, x = 1;
	memset(new, 0,(total_len)*sizeof(char));


	while(*ptr != '\0')
	{
		if(*ptr == '^')
		{
			if(counter)
			{
				strlcat(new,payload,total_len+1);
				i+=len_payload;
				counter-=1;
			}
			x++;
		} 
		else 
		{ 
			*(new+i)=*ptr;
			i++;
		}
		ptr++;
	}


	//free(new);

	return new;
}


int 
strstr_regex(char *string, char *expression)
{

	regex_t regex;
	int reti;

// Compile regular expression
	reti = regcomp(&regex, expression, REG_EXTENDED);

	if(reti)
	{ 
		DEBUG("Could not compile regex ! \n");
		DEBUG("%s ",expression);
	}
	reti = regexec(&regex, string, 0, NULL, 0);

	regfree(&regex);
  
	if( !reti )
		return 1;
	else 
		return 0;

}


char *replace(char *instring,char *old,char *new)
{ 
	int instring_size = strlen(instring), new_size = strlen(new), old_size = strlen(old), out_size = instring_size+1, count = 0;
	char *out = NULL, *tmp = NULL;
 	
	tmp = xmalloc(old_size+1);
	out = xmalloc(out_size);

	if(!out || !tmp)
 		return NULL;
    
 	if(instring_size<old_size || !old_size)
	{       
		strcpy(out, instring);
 		XFREE(tmp);
		return out;
	}   

	out[0]='\0';
    
 	while(count <= instring_size)
	{       
		strncpy(tmp,(instring+count),old_size);
		tmp[old_size] = '\0';

		if(!strcmp(tmp,old))
		{
			if(new_size!=old_size)
			{
				out_size = out_size+new_size-old_size;
				out = xreallocarray(out,out_size,sizeof(char));

				if(!out)
				{
					XFREE(tmp);
					return NULL;
				}
			}

			strcat(out,new);
			count = count+old_size-1;
		}else{
			tmp[1] = '\0';
			strcat(out,tmp);
		}

		count++;
	}

	XFREE(tmp);

	return out;
}



long parse_http_status(char * str)
{
	char part_str[32];
	strlcpy(part_str,str,32);
	char *status = strtok(part_str," ");
	status = strtok(NULL," ");
 
	if(strnlen(status,5)<= 3)
	{

		long code_num = strtol(status,(char **)NULL,10);
		return code_num;
	} else {
		return 0;
	}
}
