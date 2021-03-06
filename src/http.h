#ifndef HTTP_H
#define HTTP_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#endif

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "request.h"
#include "util.h"

typedef int (*header_handle_func)(char *, req_data_t *, res_data_t *);

typedef struct header_handler {
	const char *key;
	header_handle_func handler;

} header_handler_t;

typedef struct kv_item{
	const char *key;
	const char *value;
} kv_item;


#define PARSE_OK		0
#define PARSE_WAIT		1
#define PARSE_ERROR		-1
#define PARSE_URI_TOOLONG -2

int parse_request(req_data_t *r, int len, res_data_t *rout);
int parse_header(char *key, char *val, req_data_t *r, res_data_t *rout);
int parse_uri(req_data_t *r, res_data_t *rout);
int render(req_data_t *r, res_data_t *rout);
int render_cgi(req_data_t *r, res_data_t *rout);
int render_error(int fd, int err_code, const char *err_msg);
void * handle_request(void * request);

// Header handlers
int header_handler_ua(char *value, req_data_t *r, res_data_t *rout);
int header_handler_accept(char *value, req_data_t *r, res_data_t *rout);
int header_handler_cookie(char *value, req_data_t *r, res_data_t *rout); 
int header_handler_content_type(char *value, req_data_t *r, res_data_t *rout);
int header_handler_connection(char *value, req_data_t *r, res_data_t *rout);
int header_handler_content_length(char *value, req_data_t *r, res_data_t *rout);
int header_handler_content_type(char *value, req_data_t *r, res_data_t *rout);
int header_handler_if_modified_since(char *value, req_data_t *r, res_data_t *rout);
int header_handler_default(char *value, req_data_t *r, res_data_t *rout);

#endif
