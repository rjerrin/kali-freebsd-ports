
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



What this IT ?
this is another Web POST,GET test tool lol

need libcurl to run

$ sudo apt-get install libcurl-dev
if rpm distro
$ sudo yum install libcurl-devel
$ make
$./0d1n


*/
#ifndef VALIDATE_H__
#define VALIDATE_H__
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include <errno.h> 
#include <sys/types.h>
#include <unistd.h>
#include <curl/curl.h>
#include "mem_ops.h"




void No_Pause_Scan ();
void no_write_coredump (void); 
void load_signal_alarm (void);
void validate_hostname(const char *hostname);
int test_letter(char p);

#endif
