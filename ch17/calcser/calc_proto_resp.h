#ifndef CALC_PROTO_RESP_H
#define CALC_PROTO_RESP_H

#include <stdint.h>

typedef int status_t;

static const status_t STATUS_OK = 0;
static const status_t STATUS_INVALID_REQUEST = 1;
static const status_t STATUS_INVALID_METHOD = 2;
static const status_t STATUS_INVALID_OPERAND = 3;
static const status_t STATUS_DIV_BY_ZERO = 4;
static const status_t STATUS_INTERNAL_ERROR = 20;

struct calc_proto_resp_t {
  int32_t req_id;
  status_t status;
  double result;
};

#endif
