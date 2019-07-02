#ifndef CALC_PROTO_RESP_H
#define CALC_PROTO_RESP_H

#include <stdint.h>

#define STATUS_OK              0
#define STATUS_INVALID_REQUEST 1
#define STATUS_INVALID_METHOD  2
#define STATUS_INVALID_OPERAND 3
#define STATUS_DIV_BY_ZERO     4
#define STATUS_INTERNAL_ERROR  20

typedef int status_t;

struct calc_proto_resp_t {
  int32_t req_id;
  status_t status;
  double result;
};

#endif
