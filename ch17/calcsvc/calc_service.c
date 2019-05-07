#include <stdlib.h>

#include "calc_service.h"

struct calc_service_t {
  double mem;
};

struct calc_service_t* calc_service_new() {
  return (struct calc_service_t*)malloc(sizeof(struct calc_service_t));
}

void calc_service_delete(struct calc_service_t* svc) {
  free(svc);
}

void calc_service_ctor(struct calc_service_t* svc) {
  svc->mem = 0.0;
}

void calc_service_dtor(struct calc_service_t* svc) {}

void calc_service_reset_mem(struct calc_service_t* svc) {
  svc->mem = 0.0;
}

double calc_service_get_mem(struct calc_service_t* svc) {
  return svc->mem;
}

double calc_service_add(struct calc_service_t* svc, double a, double b,
    bool_t mem) {
  double result = a + b;
  if (!mem) {
    return result;
  }
  svc->mem = result + svc->mem;
  return svc->mem;
}

double calc_service_sub(struct calc_service_t* svc, double a, double b,
    bool_t mem) {
  double result = a - b;
  if (!mem) {
    return result;
  }
  svc->mem = result - svc->mem;
  return svc->mem;
}

double calc_service_mul(struct calc_service_t* svc, double a, double b,
    bool_t mem) {
  double result = a * b;
  if (!mem) {
    return result;
  }
  svc->mem = result * svc->mem;
  return svc->mem;
}

int calc_service_div(struct calc_service_t* svc, double a, double b, double* result) {
  if (b == 0.0) {
    return CALC_SVC_ERROR_DIV_BY_ZERO;
  }
  *result = a / b;
  return CALC_SVC_OK;
}
