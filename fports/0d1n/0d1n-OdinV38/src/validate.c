/*
Author:Antonio Costa aka " Cooler_ "
contact: c00f3r[at]gmail[dot]com


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

*/

#include "validate.h"


// block ctrl+c 
void No_Pause_Scan ()
{
	DEBUG("\n When start Scan\n You Cannot be terminated using Ctrl+C or Ctrl+Z...\n Wait task ends... press <enter> to continue... \nif you close it this can crash report in html\n");
	getchar();
	fflush(stdout);
}

void no_write_coredump (void) 
{
  	struct rlimit rlim;
   
	rlim.rlim_cur = 0; 
	rlim.rlim_max = 0; 
	setrlimit(RLIMIT_CORE, &rlim);

}

void load_signal_alarm (void)
{
 	struct sigaction sigIntHandler;

   	sigIntHandler.sa_handler = No_Pause_Scan;
   	sigemptyset(&sigIntHandler.sa_mask);
   	sigIntHandler.sa_flags = 0;

	if(sigemptyset(&sigIntHandler.sa_mask)!=0)
	{
		DEBUG("Error at signal");
		exit(1);
	}

   	if(sigaction(SIGINT, &sigIntHandler, NULL)!=0)
	{
		DEBUG("Error at signal");
		exit(1);
	}

   	if(sigaction(SIGTSTP, &sigIntHandler, NULL)!=0)
	{
		DEBUG("Error at signal");
		exit(1);
	}

   	if(sigaction(SIGQUIT, &sigIntHandler, NULL)!=0)
	{
		DEBUG("Error at signal");
		exit(1);
	}

}

void validate_hostname(const char *hostname)
{
	CURL *curl=NULL;
	CURLcode res;
 
	curl = curl_easy_init();

	if(curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, hostname);
		curl_easy_setopt(curl, CURLOPT_HEADER, 1 );
                curl_easy_setopt(curl, CURLOPT_NOBODY, 1 );
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1 );
		curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST,0); 
		curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,0); 
		

		res = curl_easy_perform(curl);
 
		if(CURLE_OK != res) 
		{
			char choice;

			DEBUG("Error validating hostname");
			printf("Do you want to continue (y/N)? ");
			if(scanf("%1c", &choice) == EOF)
				choice = 'n';

			if(choice != 'y' && choice != 'Y')
			{
				curl_easy_cleanup(curl);
				exit(0);
			}
		}

		curl_easy_cleanup(curl);
  	}
}

// DFA to test if letter between a-z or A-Z
int test_letter(char p)
{
	unsigned char yych;

	yych = p;
	switch (yych) {
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy3;
	default:	goto yy2;
	}
yy2:
	{ return 1; }
yy3:
	++p;
	{ return 0; }
    

}
