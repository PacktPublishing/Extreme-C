#ifndef COMMON_SERVER_CORE_H
#define COMMON_SERVER_CORE_H

#include <sys/socket.h>

struct client_addr_t;
struct client_context_t;

typedef void (*write_resp_func_t)(struct client_context_t*, struct calc_proto_resp_t*);

struct client_context_t {
  struct client_addr_t* addr;
  struct calc_proto_ser_t* ser;
  struct calc_service_t* svc;
  write_resp_func_t write_resp;
};

typedef void (*write_resp_func_t)(struct client_context_t*, struct calc_proto_resp_t*);

void error_callback(void* obj, int ref_id, int error_code);
void request_callback(void* obj, struct calc_proto_req_t req);

extern struct sockaddr* sockaddr_new();
extern socklen_t sockaddr_sizeof();

#endif
