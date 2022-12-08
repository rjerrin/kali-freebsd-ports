#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include <stdbool.h>
#include "validate.h"   // to validate inputs
#include "html_entities.h" // o make XSS mitigation
#include "mem_ops.h" // xmalloc() ,XFREE()...
#include "../lib/BSD/strsec.h" // strlcpy(), strlcat() and strnstr()
#include "../lib/frozen/frozen.h" // json parser
#include "../lib/libmongoose/mongoose.h" // HTTPd lib + krypton
#include "allowlist.h" // list os allowlist to access this server, file  "conf/allowlist.conf"

#define REPORT_PATH "/opt/0d1n/view/"

static struct mg_serve_http_opts s_http_server_opts;

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) 
{

	switch (ev) 
	{	
		case MG_EV_HTTP_REQUEST: {

			char addr[32];
  			mg_sock_addr_to_str(&nc->sa, addr, sizeof(addr), MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);

			if(allowlist_ip(addr)==true)
				mg_serve_http(nc, (struct http_message *)ev_data, s_http_server_opts);
      			break;
    		}
	
  	}
}
	




const char *s_ssl_cert = "/opt/0d1n/server/cert/certkey.pem";
const char *s_ssl_key = "/opt/0d1n/server/cert/privateKey.key";
const char *port = "40111"; //port to open
	
int main()
{
	struct mg_mgr mgr;
	struct mg_connection *nc;
  	struct mg_bind_opts bind_opts;
  	const char *err=NULL;

 	mg_mgr_init(&mgr, NULL);
	memset(&bind_opts, 0, sizeof(bind_opts));
  	bind_opts.ssl_cert = s_ssl_cert;
  	bind_opts.ssl_key = s_ssl_key;
  	bind_opts.error_string = &err;

  	printf("Starting SSL server on port %s, cert from %s, key from %s\n",
         port, bind_opts.ssl_cert, bind_opts.ssl_key);
  	nc = mg_bind_opt(&mgr, port, ev_handler, bind_opts);

  	if (nc == NULL) 
	{
    		DEBUG("Failed to create listener: %s\n", err);
    		return 1;
  	}

	mg_set_protocol_http_websocket(nc);

  	s_http_server_opts.document_root = REPORT_PATH;
  	s_http_server_opts.dav_document_root = REPORT_PATH;  // Allow access via WebDav
  	s_http_server_opts.enable_directory_listing = "yes";

  	fprintf(stdout,"0d1n view \nserver started at port %s\nOpen your browser in https://127.0.0.1:%s\n", port,port);


  	for (;;) 
    		mg_mgr_poll(&mgr, 1000);
  	
  
  	mg_mgr_free(&mgr);

	exit(0);
}

