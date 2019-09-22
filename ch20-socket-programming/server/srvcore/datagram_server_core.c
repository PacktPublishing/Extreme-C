#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <calc_proto_ser.h>
#include <calc_service.h>

#include "common_server_core.h"
#include "datagram_server_core.h"

struct client_addr_t {
  int server_sd;
  struct sockaddr* sockaddr;
  socklen_t socklen;
};

void datagram_write_resp(struct client_context_t* context,
        struct calc_proto_resp_t* resp) {
  struct buffer_t buf =
      calc_proto_ser_server_serialize(context->ser, resp);
  if (buf.len == 0) {
    close(context->addr->server_sd);
    fprintf(stderr, "Internal error while serializing object.\n");
    exit(1);
  }
  int ret = sendto(context->addr->server_sd, buf.data, buf.len,
      0, context->addr->sockaddr, context->addr->socklen);
  free(buf.data);
  if (ret == -1) {
    fprintf(stderr, "Could not write to client: %s\n",
            strerror(errno));
    close(context->addr->server_sd);
    exit(1);
  } else if (ret < buf.len) {
    fprintf(stderr, "WARN: Less bytes were written!\n");
    close(context->addr->server_sd);
    exit(1);
  }
}

void serve_forever(int server_sd) {
  char buffer[64];
  while (1) {
    struct sockaddr* sockaddr = sockaddr_new();
    socklen_t socklen = sockaddr_sizeof();
    int read_nr_bytes = recvfrom(server_sd, buffer,
            sizeof(buffer), 0, sockaddr, &socklen);
    if (read_nr_bytes == -1) {
      close(server_sd);
      fprintf(stderr, "Could not read from datagram socket: %s\n",
              strerror(errno));
      exit(1);
    }
    struct client_context_t context;

    context.addr = (struct client_addr_t*)
        malloc(sizeof(struct client_addr_t));
    context.addr->server_sd = server_sd;
    context.addr->sockaddr = sockaddr;
    context.addr->socklen = socklen;

    context.ser = calc_proto_ser_new();
    calc_proto_ser_ctor(context.ser, &context, 256);
    calc_proto_ser_set_req_callback(context.ser, request_callback);
    calc_proto_ser_set_error_callback(context.ser, error_callback);

    context.svc = calc_service_new();
    calc_service_ctor(context.svc);

    context.write_resp = &datagram_write_resp;

    bool_t req_found = FALSE;
    struct buffer_t buf;
    buf.data = buffer;
    buf.len = read_nr_bytes;
    calc_proto_ser_server_deserialize(context.ser, buf, &req_found);

    if (!req_found) {
      struct calc_proto_resp_t resp;
      resp.req_id = -1;
      resp.status = ERROR_INVALID_RESPONSE;
      resp.result = 0.0;
      context.write_resp(&context, &resp);
    }

    calc_service_dtor(context.svc);
    calc_service_delete(context.svc);

    calc_proto_ser_dtor(context.ser);
    calc_proto_ser_delete(context.ser);

    free(context.addr->sockaddr);
    free(context.addr);
  }
}
