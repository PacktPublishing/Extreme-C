#ifndef CALC_PROTO_SER_H
#define CALC_PROTO_SER_H

#include <types.h>

#include "calc_proto_req.h"
#include "calc_proto_resp.h"

#define ERROR_INVALID_REQUEST          101
#define ERROR_INVALID_REQUEST_ID       102
#define ERROR_INVALID_REQUEST_METHOD   103
#define ERROR_INVALID_REQUEST_OPERAND1 104
#define ERROR_INVALID_REQUEST_OPERAND2 105

#define ERROR_INVALID_RESPONSE         201
#define ERROR_INVALID_RESPONSE_REQ_ID  202
#define ERROR_INVALID_RESPONSE_STATUS  203
#define ERROR_INVALID_RESPONSE_RESULT  204

#define ERROR_UNKNOWN  220

struct buffer_t {
  char* data;
  int len;
};

struct calc_proto_ser_t;

typedef void (*req_cb_t)(
        void* owner_obj,
        struct calc_proto_req_t);

typedef void (*resp_cb_t)(
        void* owner_obj,
        struct calc_proto_resp_t);

typedef void (*error_cb_t)(
        void* owner_obj,
        const int req_id,
        const int error_code);

struct calc_proto_ser_t* calc_proto_ser_new();
void calc_proto_ser_delete(
        struct calc_proto_ser_t* ser);

void calc_proto_ser_ctor(
        struct calc_proto_ser_t* ser,
        void* owner_obj,
        int ring_buffer_size);

void calc_proto_ser_dtor(
        struct calc_proto_ser_t* ser);

void* calc_proto_ser_get_context(
        struct calc_proto_ser_t* ser);

void calc_proto_ser_set_req_callback(
        struct calc_proto_ser_t* ser,
        req_cb_t cb);

void calc_proto_ser_set_resp_callback(
        struct calc_proto_ser_t* ser,
        resp_cb_t cb);
void calc_proto_ser_set_error_callback(
        struct calc_proto_ser_t* ser,
        error_cb_t cb);

void calc_proto_ser_server_deserialize(
        struct calc_proto_ser_t* ser,
        struct buffer_t buffer,
        bool_t* req_found);

struct buffer_t calc_proto_ser_server_serialize(
        struct calc_proto_ser_t* ser,
        const struct calc_proto_resp_t* resp);

void calc_proto_ser_client_deserialize(
        struct calc_proto_ser_t* ser,
        struct buffer_t buffer,
        bool_t* resp_found);

struct buffer_t calc_proto_ser_client_serialize(
        struct calc_proto_ser_t* ser,
        const struct calc_proto_req_t* req);

#endif
