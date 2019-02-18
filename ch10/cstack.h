/* File name: cstack.h
 * Description: Declarations of the stack library
 */

#ifndef _CSTACK_H_
#define _CSTACK_H_

#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE 0

typedef int bool_t;

typedef struct {
  char* data;
  size_t len;
} value_t;

typedef struct cstack_type cstack_t;

typedef void (*deleter_t)(value_t* value);

value_t make_value(char* data, size_t len);
value_t copy_value(char* data, size_t len);
void free_value(value_t* value);

cstack_t* cstack_new();
void cstack_delete(cstack_t*);

// Behavior functions
void cstack_ctor(cstack_t*, size_t);
void cstack_dtor(cstack_t*, deleter_t);

size_t cstack_size(const cstack_t*);

bool_t cstack_push(cstack_t*, value_t value);
bool_t cstack_pop(cstack_t*, value_t* value);

void cstack_clear(cstack_t*, deleter_t);

#ifdef __cplusplus
}
#endif

#endif
