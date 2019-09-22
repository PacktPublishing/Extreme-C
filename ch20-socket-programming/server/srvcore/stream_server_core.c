#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>

#include <calc_proto_ser.h>
#include <calc_service.h>

#include "common_server_core.h"
#include "stream_server_core.h"

struct client_addr_t {
  int sd;
};

void stream_write_resp(
        struct client_context_t* context,
        struct calc_proto_resp_t* resp) {
  struct buffer_t buf = 
      calc_proto_ser_server_serialize(context->ser, resp);
  if (buf.len == 0) {
    close(context->addr->sd);
    fprintf(stderr, "Internal error while serializing response\n");
    exit(1);
  }
  int ret = write(context->addr->sd, buf.data, buf.len);
  free(buf.data);
  if (ret == -1) {
    fprintf(stderr, "Could not write to client: %s\n",
            strerror(errno));
    close(context->addr->sd);
    exit(1);
  } else if (ret < buf.len) {
    fprintf(stderr, "WARN: Less bytes were written!\n");
    exit(1);
  }
}

void* client_handler(void *arg) {
  struct client_context_t context;

  context.addr = (struct client_addr_t*)
      malloc(sizeof(struct client_addr_t));
  context.addr->sd = *((int*)arg);
  free((int*)arg);

  context.ser = calc_proto_ser_new();
  calc_proto_ser_ctor(context.ser, &context, 256);
  calc_proto_ser_set_req_callback(context.ser, request_callback);
  calc_proto_ser_set_error_callback(context.ser, error_callback);

  context.svc = calc_service_new();
  calc_service_ctor(context.svc);

  context.write_resp = &stream_write_resp;

  int ret;
  char buffer[128];
  while (1) {
    int ret = read(context.addr->sd, buffer, 128);
    if (ret == 0 || ret == -1) {
      break;
    }
    struct buffer_t buf;
    buf.data = buffer; buf.len = ret;
    calc_proto_ser_server_deserialize(context.ser, buf, NULL);
  }

  calc_service_dtor(context.svc);
  calc_service_delete(context.svc);

  calc_proto_ser_dtor(context.ser);
  calc_proto_ser_delete(context.ser);

  free(context.addr);

  return NULL;
}

void accept_forever(int server_sd) {
  while (1) {
    int client_sd = accept(server_sd, NULL, NULL);
    if (client_sd == -1) {
      close(server_sd);
      fprintf(stderr, "Could not accept the client: %s\n",
              strerror(errno));
      exit(1);
    }
    pthread_t client_handler_thread;
    int* arg = (int *)malloc(sizeof(int));
    *arg = client_sd;
    int result = pthread_create(&client_handler_thread, NULL,
            &client_handler, arg);
    if (result) {
      close(client_sd);
      close(server_sd);
      free(arg);
      fprintf(stderr, "Could not start the client handler thread.\n");
      exit(1);
    }
  }
}
