#include "file_ops.h"
#include "mem_ops.h"
#include "string_ops.h"
#include "strsec.h"
#include "opt_extract.h"

void 
end_datatable(char * path)
{
	write_file(path," [\"\",\"\",\"\",\"\",\"\",\"\"] \n ] }");
}

void 
prepare_datatable(void)
{
	int num1 = 0, num2 = 0;
	char *pathtable = NULL, *pathhammer = NULL, *view = NULL, *template2 = NULL, *template3 = NULL;

       	// write tables rowsin datatables file to renderize html+js table...
	pathtable = xmalloc(128*sizeof(char));
	memset(pathtable,0, 127*sizeof(char));
	strlcat(pathtable,PATH_RESULT,16);
	strlcat(pathtable,"tables/",25);
	strlcat(pathtable,param.log, strlen(param.log)+25);
	strlcat(pathtable,".txt",strlen(pathtable)+6);

	//prepare templates for HTML report
	num1 = file_size(TEMPLATE2);
        num2 = file_size(TEMPLATE3); 
	size_t total = num1+num2+512;
	view = xmallocarray(total,sizeof(char));
	memset(view,0,(total-1)*sizeof(char));
        template2 = read_lines(TEMPLATE2);

	// prepare JSON to render on datatables
	strlcat(view,template2,(num1+1)*sizeof(char));
	strlcat(view,"\"sAjaxSource\": \"",num1+24);
	strlcat(view,param.log,num1+64);
	strlcat(view,".txt\" \n",num1+112);
        template3 = read_lines(TEMPLATE3);
	strlcat(view,template3,total);
	strlcat(view,template3,num2+num1+112);

	// path of template
	pathhammer = xmalloc(64*sizeof(char));
	memset(pathhammer,0,63*sizeof(char));
	strlcat(pathhammer,"/opt/0d1n/view/tables/hammer_",40);
	strlcat(pathhammer,param.log,50);
	strlcat(pathhammer,".html",55);
	write_file(pathhammer,view);
	write_file(pathtable,"{ \"aaData\": [ \n");

	XFREE(view);
	XFREE(template2);
	XFREE(template3);

	param.path_output = pathhammer;
	param.datatable = pathtable;
}


//read lines of file
char 
*read_lines (char * NameFile)
{
	FILE * arq;

	arq = fopen(NameFile, "r");

	if( arq == NULL )
	{
		DEBUG("error in filename %s  to open() file:  %s",NameFile,strerror(errno));		
		exit(0);
	}

	fseek(arq, 0, SEEK_END);
    	long length = ftell(arq);
    	fseek(arq, 0, SEEK_SET);
    	char *buffer = xmalloc(sizeof(char)*(length + 1));
    	buffer[length] = '\0';
	
    	if (fread(buffer, sizeof(char), length, arq)<=0)
	{
		DEBUG("Config error Empty rule file %s",NameFile);
		exit(0);
	}
 
	if (fclose(arq) == EOF)
	{
		DEBUG("Error in close() file %s",NameFile);
		exit(0);
	}

	arq = NULL;

	return buffer;
}

// write line in file
int 
write_file (char *file,char *str)
{
	FILE *fp;
	int res = 0;
 	short tolerate = 5;

	WRITE_POINT:
	fp = fopen(file,"a");
       	

	if ( fp == NULL ) 
	{
//		fclose(arq);
		DEBUG("error in write_file() %s: %s\nBuffer log: %s \n",file,strerror(errno),str); 
		tolerate-=1;
		sleep(5);

		if(tolerate>0)
			goto WRITE_POINT;
		else
			exit(0);
	}

	res = fprintf(fp,"%s\n",str); 
	if(res < 1)
	{
		fclose(fp);
		return 0;
	}

	if (fclose(fp) == EOF )
	{
		DEBUG("error in Close() file %s \n %s\n",file,strerror(errno));
		exit(0);
	}

	fp = NULL;
 

	return 1;
}

// return size of bytes on file , same to unix cmd "du -b file"
long 
file_size(const char *file)
{
	long ret;
	FILE *arq; 

        arq = fopen(file, "r");

	if ( arq == NULL )
	{
	//	fclose(arq);
		DEBUG("error in file %ss : %s ",file,strerror(errno));
		exit(0);
	}

	fseek(arq, 0, SEEK_END);
	ret = ftell(arq);

	if( fclose(arq) == EOF )
	{
  		DEBUG("error in close() file %s",file);
		exit(0);
	}

	arq = NULL;

	return ret;
}



// returns random line from file
char *
Random_linefile(char * namefile)
{
	FILE *f;
	int nLines = 0;
	static char line[1024];   // think recv space to nullbyte 1023
	int randLine = 0, i = 0; 

	entropy_clock();  // i set entropy seed here

	memset(line,0x0,1023);


	f = fopen(namefile, "r");

	if ( f == NULL )
	{
		fprintf(stderr, "Error opening file: %s\n", strerror(errno) );
//		fclose(f);
		DEBUG("error in file %s",namefile);
		exit(0);
	}

	while ( !feof(f) )
	{
		if(fgets(line, 1023, f)!=NULL) 
			nLines++;
	}

	randLine = rand() % nLines;

	fseek(f, 0, SEEK_SET);

	while (!feof(f) && i <= randLine)
		if(fgets(line, 1023, f)!=NULL)
			i++;
				
	if( fclose(f) == EOF )
	{
  		DEBUG("error in close() file %s",namefile);
		exit(0);
	}

	f = NULL;

    	return line;
}
