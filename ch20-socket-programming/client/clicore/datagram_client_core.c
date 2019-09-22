#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#include <sys/socket.h>

#include "common_client_core.h"

void* datagram_response_reader(void* obj) {
  struct context_t* context = (struct context_t*)obj;
  char buf[64];
  while (1) {
    // We could use `read` since we don't need the source address.
    int ret = recvfrom(context->sd, buf, sizeof(buf), 0, NULL, NULL);
    if (ret < 0) {
      fprintf(stderr, "Read error! %s\n", strerror(errno));
      break;
    }
    if (ret == 0) {
      break;
    }
    struct buffer_t b; b.data = buf, b.len = ret;
    calc_proto_ser_client_deserialize(context->ser, b, NULL);
  }
  return NULL;
}

void datagram_client_loop(int conn_sd) {
  struct context_t context;

  context.sd = conn_sd;
  context.ser = calc_proto_ser_new();
  calc_proto_ser_ctor(context.ser, &context, 128);
  calc_proto_ser_set_resp_callback(context.ser, on_response);
  calc_proto_ser_set_error_callback(context.ser, on_error);

  pthread_t reader_thread;
  pthread_create(&reader_thread, NULL, datagram_response_reader, &context);

  char buffer[128];
  printf("? (type quit to exit) ");
  while (1) {
    scanf("%s", buffer);
    int brk = 0, cnt = 0;
    struct calc_proto_req_t req;
    parse_client_input(buffer, &req, &brk, &cnt);
    if (brk) {
      break;
    }
    if (cnt) {
      continue;
    }
    struct buffer_t buf = calc_proto_ser_client_serialize(context.ser, &req);
    // We could use `write` since we already know the destination.
    int ret = write(context.sd, buf.data, buf.len);
    free(buf.data);
    if (ret == -1) {
      fprintf(stderr, "Error while writing! %s\n", strerror(errno));
      break;
    }
    if (ret < buf.len) {
      fprintf(stderr, "Wrote less than anticipated!\n");
      break;
    }
    printf("The req(%d) is sent.\n", req.id);
  }
  shutdown(conn_sd, SHUT_RD);
  pthread_join(reader_thread, NULL);
  calc_proto_ser_dtor(context.ser);
  calc_proto_ser_delete(context.ser);
  printf("Bye.\n");
}
