// File name: ExtremeC_examples_chapter18_4_shared_int32.c
// Description: Implementation of the shared_int32 class.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "ExtremeC_examples_chapter18_4_shared_mem.h"

typedef struct {
  struct shared_mem_t* shm;
  int32_t* ptr;
} shared_int32_t;

shared_int32_t* shared_int32_new(const char* name) {
  shared_int32_t* obj =
      (shared_int32_t*)malloc(sizeof(shared_int32_t));
  obj->shm = shared_mem_new();
  return obj;
}

void shared_int32_delete(shared_int32_t* obj) {
  shared_mem_delete(obj->shm);
  free(obj);
}

void shared_int32_ctor(shared_int32_t* obj, const char* name) {
  shared_mem_ctor(obj->shm, name, sizeof(int32_t));
  obj->ptr = (int32_t*)shared_mem_getptr(obj->shm);
}

void shared_int32_dtor(shared_int32_t* obj) {
  shared_mem_dtor(obj->shm);
}

void shared_int32_setvalue(shared_int32_t* obj, int32_t value) {
  *(obj->ptr) = value;
}

void shared_int32_setvalue_ifowner(shared_int32_t* obj,
                                   int32_t value) {
  if (shared_mem_isowner(obj->shm)) {
    *(obj->ptr) = value;
  }
}

int32_t shared_int32_getvalue(shared_int32_t* obj) {
  return *(obj->ptr);
}
