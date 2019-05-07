#include <string.h>

#include "calc_proto_req.h"

static char GETMEM_STR[] = "GETMEM";
static char RESMEM_STR[] = "RESMEM";
static char ADD_STR[]    = "ADD";
static char ADDM_STR[]   = "ADDM";
static char SUB_STR[]    = "SUB";
static char SUBM_STR[]   = "SUBM";
static char MUL_STR[]    = "MUL";
static char MULM_STR[]   = "MULM";
static char DIV_STR[]    = "DIV";

method_t str_to_method(const char* str) {
  if (!strcmp(str, GETMEM_STR)) return GETMEM;
  if (!strcmp(str, RESMEM_STR)) return RESMEM;
  if (!strcmp(str, ADD_STR   )) return ADD;
  if (!strcmp(str, ADDM_STR  )) return ADDM;
  if (!strcmp(str, SUB_STR   )) return SUB;
  if (!strcmp(str, SUBM_STR  )) return SUBM;
  if (!strcmp(str, MUL_STR   )) return MUL;
  if (!strcmp(str, MULM_STR  )) return MULM;
  if (!strcmp(str, DIV_STR   )) return DIV;
  return 0;
}

const char* method_to_str(method_t method) {
  switch (method) {
    case GETMEM: return GETMEM_STR;
    case RESMEM: return RESMEM_STR;
    case ADD:    return ADD_STR;
    case ADDM:   return ADDM_STR;
    case SUB:    return SUB_STR;
    case SUBM:   return SUBM_STR;
    case MUL:    return MUL_STR;
    case MULM:   return MULM_STR;
    case DIV:    return DIV_STR;
    default:     return NULL;
  }
}
