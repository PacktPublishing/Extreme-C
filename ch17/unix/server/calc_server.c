#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>

#include <calc_proto_ser.h>
#include <calc_service.h>

struct client_context_t {
  int fd;
  struct calc_proto_ser_t* ser;
  struct calc_service_t* svc;
};

void _write_resp(struct client_context_t* context, struct calc_proto_resp_t* resp) {
  struct buffer_t buf = calc_proto_ser_server_serialize(context->ser, resp);
  if (buf.len == 0) {
    close(context->fd);
    fprintf(stderr, "Internal error while serializing response object.\n");
    exit(1);
  }
  int ret = write(context->fd, buf.data, buf.len);
  free(buf.data);
  if (ret < buf.len) {
    fprintf(stderr, "WARN: Less bytes were written!\n");
  } else if (ret == -1) {
    fprintf(stderr, "Could not write to client: %s\n", strerror(errno));
    close(context->fd);
  }
}

void error_callback(void* obj, int ref_id, int error_code) {
  struct client_context_t* context = (struct client_context_t*)obj;
  int status = STATUS_INTERNAL_ERROR;
  switch (error_code) {
    case ERROR_INVALID_REQUEST:
      status = STATUS_INVALID_REQUEST; break;
    case ERROR_INVALID_REQUEST_ID:
      status = STATUS_INVALID_REQUEST; break;
    case ERROR_INVALID_REQUEST_METHOD:
      status = STATUS_INVALID_METHOD; break;
    case ERROR_INVALID_REQUEST_OPERAND1:
      status = STATUS_INVALID_OPERAND; break;
    case ERROR_INVALID_REQUEST_OPERAND2:
      status = STATUS_INVALID_OPERAND; break;
    case ERROR_UNKNOWN:
    default:
      break;
  }
  struct calc_proto_resp_t resp;
  resp.req_id = ref_id;
  resp.status = status;
  resp.result = 0.0;
  _write_resp(context, &resp);
}

void request_callback(void* obj, struct calc_proto_req_t req) {
  struct client_context_t* context = (struct client_context_t*)obj;
  int status = STATUS_OK;
  double result = 0.0;
  switch (req.method) {
    case GETMEM:
      result = calc_service_get_mem(context->svc);
      break;
    case RESMEM:
      calc_service_reset_mem(context->svc);
      break;
    case ADD:
    case ADDM:
      result = calc_service_add(context->svc, req.operand1,
          req.operand2, req.method == ADDM);
      break;
    case SUB:
    case SUBM:
      result = calc_service_mul(context->svc, req.operand1,
          req.operand2, req.method == SUBM);
      break;
    case MUL:
    case MULM:
      result = calc_service_mul(context->svc, req.operand1,
          req.operand2, req.method == MULM);
      break;
    case DIV: {
      status = calc_service_div(context->svc, req.operand1,
          req.operand2, &result);
      if (status == CALC_SVC_ERROR_DIV_BY_ZERO) {
        status = STATUS_DIV_BY_ZERO;
      }
      break;
    }
    default:
      status = STATUS_INVALID_METHOD;
  }
  struct calc_proto_resp_t resp;
  resp.req_id = req.id;
  resp.status = status;
  resp.result = result;
  _write_resp(context, &resp);
}

void* client_handler(void *arg) {
  struct client_context_t context;

  context.fd = *((int*)arg);

  context.ser = calc_proto_ser_new();
  calc_proto_ser_ctor(context.ser, &context, 256);
  calc_proto_ser_set_req_callback(context.ser, request_callback);
  calc_proto_ser_set_error_callback(context.ser, error_callback);

  context.svc = calc_service_new();
  calc_service_ctor(context.svc);

  int ret;
  char buffer[128];
  while (1) {
    int ret = read(context.fd, buffer, 128);
    if (ret == 0 || ret == -1) {
      break;
    }
    struct buffer_t buf;
    buf.data = buffer; buf.len = ret;
    calc_proto_ser_server_deserialize(context.ser, buf);
  }

  calc_service_dtor(context.svc);
  calc_service_delete(context.svc);

  calc_proto_ser_dtor(context.ser);
  calc_proto_ser_delete(context.ser);

  free((int*)arg);

  return NULL;
}

void accept_forever(int server_fd) {
  while (1) {
    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) {
      close(server_fd);
      fprintf(stderr, "Could not accept the client: %s\n", strerror(errno));
      exit(1);
    }
    pthread_t client_handler_thread;
    int* arg = (int *)malloc(sizeof(int));
    *arg = client_fd;
    int result = pthread_create(&client_handler_thread, NULL, &client_handler, arg);
    if (result) {
      close(client_fd);
      close(server_fd);
      free(arg);
      fprintf(stderr, "Could not start the client handler thread.\n");
      exit(1);
    }
  }
}
