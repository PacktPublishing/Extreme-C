/* File name: cstack_tests.c
 * Description: Testing the stack library
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "cstack.h"

value_t make_int(int int_value) {
  value_t value;
  int* int_ptr = (int*)malloc(sizeof(int));
  *int_ptr = int_value;
  value.data = (char*)int_ptr;
  value.len = sizeof(int);
  return value;
}

int extract_int(value_t* value) {
  return *((int*)value->data);
}

void deleter(value_t* value) {
  if (value->data) {
    free(value->data);
  }
  value->data = NULL;
}

int main(int argc, char** argv) {
  cstack_t* cstack = cstack_new();
  cstack_ctor(cstack, 100);
  assert(cstack_size(cstack) == 0);

  int int_values[] = {5, 10, 20, 30};

  for (size_t i = 0; i < 4; i++) {
    cstack_push(cstack, make_int(int_values[i]));
  }
  assert(cstack_size(cstack) == 4);

  int counter = 3;
  value_t value;
  while (cstack_size(cstack) > 0) {
    bool_t popped = cstack_pop(cstack, &value);
    assert(popped);
    assert(extract_int(&value) == int_values[counter--]);
    deleter(&value);
  }
  assert(counter == -1);
  assert(cstack_size(cstack) == 0);

  cstack_push(cstack, make_int(10));
  cstack_push(cstack, make_int(20));
  assert(cstack_size(cstack) == 2);

  cstack_clear(cstack, deleter);
  assert(cstack_size(cstack) == 0);

   // In order to have something in the stack while
  // calling destructor.
  cstack_push(cstack, make_int(20));

  cstack_dtor(cstack, deleter);
  cstack_delete(cstack);
  printf("All tests were OK.\n");
  return 0;
}
