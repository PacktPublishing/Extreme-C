// File name: ExtremeC_examples_chapter15_4_shared_cond.c
// Description: Implementation of the shared_cond class.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

#include "ExtremeC_examples_chapter15_4_shared_mem.h"
#include "ExtremeC_examples_chapter15_4_shared_mutex.h"

typedef struct {
  struct shared_mem_t* shm;
  pthread_cond_t* ptr;
} shared_cond_t;

shared_cond_t* shared_cond_new() {
  shared_cond_t* obj = (shared_cond_t*)malloc(sizeof(shared_cond_t));
  obj->shm = shared_mem_new();
  return obj;
}

void shared_cond_delete(shared_cond_t* obj) {
  shared_mem_delete(obj->shm);
  free(obj);
}

void shared_cond_ctor(shared_cond_t* obj, const char* name) {
  shared_mem_ctor(obj->shm, name, sizeof(pthread_cond_t));
  obj->ptr = (pthread_cond_t*)shared_mem_getptr(obj->shm);
  pthread_condattr_t attr;
  if (pthread_condattr_init(&attr)) {
    fprintf(stderr, "ERROR(%s): Initializing cv attrs failed: %s\n",
        name, strerror(errno));
    exit(1);
  }
  if (pthread_condattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)) {
    fprintf(stderr, "ERROR(%s): Setting the cv attr failed: %s\n",
        name, strerror(errno));
    exit(1);
  }
  if (pthread_cond_init(obj->ptr, &attr)) {
    fprintf(stderr, "ERROR(%s): Initializing the cv failed: %s\n",
        name, strerror(errno));
    exit(1);
  }
  if (pthread_condattr_destroy(&attr)) {
    fprintf(stderr, "ERROR(%s): Destruction of cv attrs failed: %s\n",
        name, strerror(errno));
    exit(1);
  }
}

void shared_cond_dtor(shared_cond_t* obj) {
  if (pthread_cond_destroy(obj->ptr)) {
    fprintf(stderr, "WARN: Destruction of the cv failed: %s\n",
        strerror(errno));
  }
  shared_mem_dtor(obj->shm);
}

void shared_cond_wait(shared_cond_t* obj,
                      struct shared_mutex_t* mutex) {
  if (pthread_cond_wait(obj->ptr, shared_mutex_getptr(mutex))) {
    fprintf(stderr, "WARN: Waiting on the cv failed: %s\n",
        strerror(errno));
  }
}

void shared_cond_broadcast(shared_cond_t* obj) {
  if (pthread_cond_signal(obj->ptr)) {
    fprintf(stderr, "WARN: Broadcasting on the cv failed: %s\n",
        strerror(errno));
  }
}
