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

#ifndef OPT_EXTRACT_H__
#define OPT_EXTRACT_H__

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <getopt.h>

#include "scan.h"
#include "validate.h"


struct choice  {
	char *host;
	char *payloads;
	char *custom;
	char *find_string_list;
	char *find_regex_list;
	char *cookie_jar;
	char *cookie;
	char *agent;
	char *post;
	char *method;
	char *header;
	char *log;
	char *UserAgent;
	char *CA_certificate;
	char *SSL_version;
	char *threads;
	char *timeout;
	char *proxy;
	char *proxy_rand;
	char *useragent_rand;
	char *tamper;
	char *token_name;
	char *path_output;
	char *datatable;
	bool save_response;
	bool race_test;
	bool json_headers;
	bool keep_alive_test;
	int max_requests;
};

struct bufferglobal {
	char *buf_useragent;
	char *buf_proxy;
	char *buf_list;
	char *buf_payloads;
	char *buf_custom;
	int useragent_lines;
	int proxy_lines;
};


extern struct choice param;
extern struct bufferglobal blob;

void load_files();
void init_banner_odin();
void parser_opts (int argc, char **argv);

#endif
