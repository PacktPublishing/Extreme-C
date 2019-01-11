// File name: ExtremeC_examples_chapter11_11_shared_mutex.c
// Description: Implementation of the shared_mutex class.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

#include "ExtremeC_examples_chapter11_11_shared_mem.h"

typedef struct {
  struct shared_mem_t* shm;
  pthread_mutex_t* ptr;
} shared_mutex_t;

shared_mutex_t* shared_mutex_new() {
  shared_mutex_t* obj = (shared_mutex_t*)malloc(sizeof(shared_mutex_t));
  obj->shm = shared_mem_new();
  return obj;
}

void shared_mutex_delete(shared_mutex_t* obj) {
  shared_mem_delete(obj->shm);
  free(obj);
}

void shared_mutex_ctor(shared_mutex_t* obj, const char* name) {
  shared_mem_ctor(obj->shm, name, sizeof(pthread_mutex_t));
  obj->ptr = (pthread_mutex_t*)shared_mem_getptr(obj->shm);
  pthread_mutexattr_t attr;
  if (pthread_mutexattr_init(&attr)) {
    fprintf(stderr, "ERROR(%s): Initializing mutex attrs failed: %s\n",
        name, strerror(errno));
    exit(1);
  }
  if (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)) {
    fprintf(stderr, "ERROR(%s): Setting the mutex attr failed: %s\n",
        name, strerror(errno));
    exit(1);
  }
  if (pthread_mutex_init(obj->ptr, &attr)) {
    fprintf(stderr, "ERROR(%s): Initializing the mutex failed: %s\n",
        name, strerror(errno));
    exit(1);
  }
  if (pthread_mutexattr_destroy(&attr)) {
    fprintf(stderr, "ERROR(%s): Destruction of mutex attrs failed: %s\n",
        name, strerror(errno));
    exit(1);
  }
}

void shared_mutex_dtor(shared_mutex_t* obj) {
  if (pthread_mutex_destroy(obj->ptr)) {
    fprintf(stderr, "WARN: Destruction of the mutex failed: %s\n",
        strerror(errno));
  }
  shared_mem_dtor(obj->shm);
}

pthread_mutex_t* shared_mutex_getptr(shared_mutex_t* obj) {
  return obj->ptr;
}

void shared_mutex_lock(shared_mutex_t* obj) {
  if (pthread_mutex_lock(obj->ptr)) {
    fprintf(stderr, "WARN: Locking the mutex failed: %s\n",
        strerror(errno));
  }
}

void shared_mutex_unlock(shared_mutex_t* obj) {
  if (pthread_mutex_unlock(obj->ptr)) {
    fprintf(stderr, "WARN: Unlocking the mutex failed: %s\n",
        strerror(errno));
  }
}
