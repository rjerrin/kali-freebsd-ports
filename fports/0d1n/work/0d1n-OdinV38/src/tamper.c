#include "tamper.h"
#include "mem_ops.h"
#include "string_ops.h"

char * tamper_choice(char * tamper,char *line)
{
	bool test_tamper=false;
			
		if(strstr(tamper,"encode64"))
		{
			line=encode64(line,strlen(line)-1);
			test_tamper=true;
		}

		if(strstr(tamper,"randcase"))
		{
			line=rand_case(line);
			test_tamper=true;
		}


		if(strstr(tamper,"urlencode"))
		{
			line=urlencode(line);
			test_tamper=true;
		}

		if(strstr(tamper,"double_urlencode"))
		{
			line=double_urlencode(line);
			test_tamper=true;
		}

		if(strstr(tamper,"spaces2comment"))
		{
			line=spaces2comment(line);
			test_tamper=true;
		}

		if(strstr(tamper,"unmagicquote"))
		{
			line=unmagicquote(line);
			test_tamper=true;
		}


		if(strstr(tamper,"apostrophe2nullencode"))
		{
			line=apostrophe2nullencode(line);
			test_tamper=true;
		}

		if(strstr(tamper,"rand_comment"))
		{
			line=rand_comment(line);
			test_tamper=true;
		}



		if(strstr(tamper,"rand_space"))
		{
			line=rand_space(line);
			test_tamper=true;
		}



		if(strstr(tamper,"replace_keywords"))
		{
			line=replace_keywords(line);
			test_tamper=true;
		}


		if(test_tamper==false)
		{
			DEBUG("error at tamper argument\n");
			exit(0);
		}


	return line;
}


char *encode64(char* input, int len) 
{
    int leftposition = len % 3,n = 0,outlen = 0;
    char *ret = xmallocarray(((len/3) * 4) + ((leftposition)?4:0) + 1,sizeof(char));
    uint8_t i = 0;
    uint8_t *ptr = (uint8_t *) input;
    const char *list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz"
                        "0123456789+/";

    if (ret == NULL)
        return NULL;

    // Convert each 3 bytes of input to 4 bytes of output.
    len -= leftposition;
    for (n = 0; n < len; n+=3) 
    {
        i = ptr[n] >> 2;
        ret[outlen++] = list[i];

        i  = (ptr[n]   & 0x03) << 4;
        i |= (ptr[n+1] & 0xf0) >> 4;
        ret[outlen++] = list[i];

        i  = ((ptr[n+1] & 0x0f) << 2);
        i |= ((ptr[n+2] & 0xc0) >> 6);
        ret[outlen++] = list[i];

        i  = (ptr[n+2] & 0x3f);
        ret[outlen++] = list[i];
    }

    // Handle leftposition 1 or 2 bytes.
    if (leftposition) 
    {
        i = (ptr[n] >> 2);
        ret[outlen++] = list[i];

        i = (ptr[n]   & 0x03) << 4;

        if (leftposition == 2) 
	{
            i |= (ptr[n+1] & 0xf0) >> 4;
            ret[outlen++] = list[i];

            i  = ((ptr[n+1] & 0x0f) << 2);
        }

        ret[outlen++] = list[i];
        ret[outlen++] = '=';
        if (leftposition == 1)
            ret[outlen++] = '=';
    }
    ret[outlen] = '\0';
    return ret;
}


// random case return string, input= tomato output=ToMatO or tOmATo...
char *rand_case(char *str)
{
	char *str_new=xmallocarray(strlen(str)+1,sizeof(char));
	int i=0;
	
	while(*str != '\0')
	{
		
		if(!test_letter( *str ) )
		{
			entropy_clock();
// uppercase or lowercase condition
			if( (rand()%3) != 2)
				*(str_new+i)=*str & ~0x20;
			else
				*(str_new+i)=*str | 0x20;
	
			i++;
		} else {
			*(str_new+i)=*str;
			i++;
		}

	
		str++;	
	}

	return str_new;

}
 
char *urlencode( char *str )
{
	char *buf=NULL,*ptr=NULL;
	char hex[] = "0123456789ABCDEF";
  
	buf = xmallocarray( strlen(str) << 2,sizeof(char) );
	ptr = buf;
  
	while(*str)
	{
		if( isalnum(*str) || *str == '-' || *str == '_' || *str == '.' || *str == '~' )
			*ptr++ = *str;
		else if( *str == ' ' )
			*ptr++ = '+';
         	else {
			*ptr++ = '%';
			*ptr++ = hex [(*str >> 4)&15];
       			*ptr++ = hex [(*str & 15)&15];
         	}
		str++;
	}

	*ptr = '\0';

	return buf;
}
  
char *double_urlencode( char *str )
{
	char *buf=NULL,*buf2=NULL,*ptr=NULL;

	char hex[] = "0123456789ABCDEF";
  
	buf = xmallocarray( strlen(str) << 2,sizeof(char) );
	ptr = buf;
  
	while(*str)
	{
		if( isalnum(*str) || *str == '-' || *str == '_' || *str == '~' )
			*ptr++ = *str;
		else if( *str == ' ' )
			*ptr++ = '+';
         	else {
			*ptr++ = '%'; // i think optimize change this to %25
			*ptr++ = hex [(*str >> 4)&15];
       			*ptr++ = hex [(*str & 15)&15];
         	}
		str++;
	}

	*ptr = '\0';
	buf2 = xmallocarray( strlen(buf) << 2,sizeof(char) );
	buf2 = urlencode(buf);

	if(buf!=NULL)
	{
		free(buf);
		buf=NULL;
	}

	return buf2;
}


char *spaces2comment(char *str)
{
 char *out=replace(str," ","/**/");
 
 return out;
}



char *unmagicquote(char *str)
{
 char *out=replace(str,"'","%bf%27");
 
 return out;
}


char *apostrophe2nullencode(char *str)
{
 char *out=replace(str,"'","%00%27");
 
 return out;
}


char *rand_comment(char *str)
{
	int i=0, mem_size=strlen(str)+1;
	char *str_new=xmallocarray(mem_size,sizeof(char));
		
	while(*str != '\0')
	{
		
		if(!test_letter( *str ) )
		{
			entropy_clock();

			if( (rand()%16) < 4)
			{
				mem_size+=4;
				str_new=xreallocarray(str_new,sizeof(char),mem_size);
				*(str_new+i)=*str;
				i++;
				*(str_new+i)='/';
				i++;
				*(str_new+i)='*';
				i++;
				*(str_new+i)='*';
				i++;
				*(str_new+i)='/';
			} else {
				*(str_new+i)=*str;
			}
			i++;
		} else {
			*(str_new+i)=*str;
			i++;
		}

	
		str++;	
	}


	return str_new;

}



char *rand_space(char *str)
{
	int i=0,mem_size=strlen(str)+1;
	char *str_new=xmallocarray(mem_size,sizeof(char));
		
	while(*str != '\0')
	{
		
		if(*str == ' ' )
		{
			entropy_clock();

			if( (rand()%4) <= 2)
			{
				mem_size+=4;
				str_new=xreallocarray(str_new,mem_size,sizeof(char));
				*(str_new+i)=*str;
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
			} else {	
				mem_size+=10;
				str_new=xreallocarray(str_new,mem_size,sizeof(char));
				*(str_new+i)=*str;
				i++;
				*(str_new+i)=' ';     // Loop unrolling...
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
				i++;
				*(str_new+i)=' ';
			}
			i++;
		} else {
			*(str_new+i)=*str;
			i++;
		}

	
		str++;	
	}

	return str_new;
}


char *replace_keywords(char *str)
{
 int mem_size=strlen(str)+1;
 char *out=xmallocarray(mem_size,sizeof(char));
 char *strs[] = {"select", "union", "delete", "script","where","from","and","eval","exec","or","update","sleep"};
 char *strs2[] = {"selselectect", "uniunionon", "deldeleteete", "scrscriptipt","whewherere","frfromom","anandd","evevalal","exexecec","oorr","updupdateate","slesleepep"};
 short num=10;

	 strlcpy(out,str,mem_size);

	do {
		char *tmp=replace(out,strs[num],strs2[num]);
		mem_size=strlen(tmp)+1;
		out=xreallocarray(out,mem_size,sizeof(char));
		strlcpy(out,tmp,mem_size);
		if(tmp != NULL)
		{
			free(tmp);
			tmp=NULL;
		}
		num--;
	} while(num!=-1);

 return out;
}
