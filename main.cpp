#include <iostream>
#include "mongoose.c"


static const char * s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
static void ev_handler(struct mg_connection *c, int ev, void *p){

	if(ev == MG_EV_HTTP_REQUEST){
		mg_serve_http(c, (struct http_message *) p , s_http_server_opts);
	}	

}

int main(void){

	struct mg_mgr mgr;
	struct mg_connection *c;

	mg_mgr_init(&mgr, NULL);
	c = mg_bind(&mgr, s_http_port, ev_handler);
	if(c == NULL){
		std::cout << "Failed to create listener\n";
		return 1;
	}	
	//http server paramaters
	
	mg_set_protocol_http_websocket(c);
	s_http_server_opts.document_root = "root/";
	s_http_server_opts.enable_directory_listing = "yes";

	for(;;){
		mg_mgr_poll(&mgr,1000);
	}
	mg_mgr_free(&mgr);
	return 0;
}



