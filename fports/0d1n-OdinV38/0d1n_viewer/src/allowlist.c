#include "allowlist.h"

// test IP using allowlist
bool allowlist_ip(char * addr)
{
	FILE * arq;
	bool at_list=false;

	arq = fopen("/opt/0d1n/server/allowlist.txt", "r");

	if( arq == NULL )
	{

		DEBUG("error to open() file"); 	 
		exit(1);
	}

	char line[128];
	memset(line,0,128);

	while( fgets(line,sizeof line,arq) && at_list==false )
	{
		line[strlen(line)-1]='\0';

// the allowlist can accept regex: 127.0.0.* ...
		if(strstr(addr,line))
			at_list=true;
	}

	if( fclose(arq) == EOF )
	{
		DEBUG("Error in close() conf/allowlist.conf ");
		exit(1);
	}

	arq=NULL;

	return at_list;
}



