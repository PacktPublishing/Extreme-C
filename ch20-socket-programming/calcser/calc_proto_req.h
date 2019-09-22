#ifndef CALC_PROTO_REQ_H
#define CALC_PROTO_REQ_H

#include <stdint.h>

typedef enum {
  NONE,
  GETMEM, RESMEM,
  ADD, ADDM,
  SUB, SUBM,
  MUL, MULM,
  DIV
} method_t;

struct calc_proto_req_t {
  int32_t id;
  method_t method;
  double operand1;
  double operand2;
};

method_t str_to_method(const char*);
const char* method_to_str(method_t);

#endif
