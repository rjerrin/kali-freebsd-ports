/*
Author:Antonio Costa aka " Cooler_ "
contact: coolerlair[at]gmail[dot]com


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
#include <stdio.h> 
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include "opt_extract.h"
#include "scan.h"
#include "validate.h"
#include "get_csrf_token.h"



int 
main (int argc, char ** argv)
{
 	no_write_coredump();
 	load_signal_alarm();
	parser_opts(argc,argv);
// So new versions of GCC skip pthreads with file systems ops, 
// This cause anomaly in threads when you use with strtok() resources in loop.
// why ? i don't know, maybe need study internals of LLVM/GCC to make a report  ¯\_(ツ)_/¯
// this source code have a different scan() function to bypass the compiler bug
/* remove comment to test the patch
*/
#ifdef __GNUC__
#  if __GNUC_PREREQ(10,0)

	scan_gcc_new();
#  else
	scan_gcc_old();
#  endif
#endif

 	exit(0);
}

