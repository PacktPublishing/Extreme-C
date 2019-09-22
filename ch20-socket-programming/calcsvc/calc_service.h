#ifndef CALC_SERVICE_H
#define CALC_SERVICE_H

#include <types.h>

static const int CALC_SVC_OK = 0;
static const int CALC_SVC_ERROR_DIV_BY_ZERO = -1;

struct calc_service_t;

struct calc_service_t* calc_service_new();
void calc_service_delete(struct calc_service_t*);

void calc_service_ctor(struct calc_service_t*);
void calc_service_dtor(struct calc_service_t*);

void calc_service_reset_mem(struct calc_service_t*);
double calc_service_get_mem(struct calc_service_t*);
double calc_service_add(struct calc_service_t*, double, double b,
    bool_t mem);
double calc_service_sub(struct calc_service_t*, double, double b,
    bool_t mem);
double calc_service_mul(struct calc_service_t*, double, double b,
    bool_t mem);
int calc_service_div(struct calc_service_t*, double,
        double, double*);

#endif
