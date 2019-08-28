// File name: ExtremeC_examples_chapter18_4_shared_cond.c
// Description: Implementation of the shared_cond class.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

#include "ExtremeC_examples_chapter18_4_shared_mem.h"
#include "ExtremeC_examples_chapter18_4_shared_mutex.h"

typedef struct {
  struct shared_mem_t* shm;
  pthread_cond_t* ptr;
} shared_cond_t;

shared_cond_t* shared_cond_new() {
  shared_cond_t* obj =
      (shared_cond_t*)malloc(sizeof(shared_cond_t));
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
  if (shared_mem_isowner(obj->shm)) {
    pthread_condattr_t cond_attr;
    int ret = -1;
    if ((ret = pthread_condattr_init(&cond_attr))) {
      fprintf(stderr,
          "ERROR(%s): Initializing cv attrs failed: %s\n",
          name, strerror(ret));
      exit(1);
    }
    if ((ret = pthread_condattr_setpshared(&cond_attr,
                    PTHREAD_PROCESS_SHARED))) {
      fprintf(stderr, 
          "ERROR(%s): Setting as process shared failed: %s\n",
          name, strerror(ret));
      exit(1);
    }
    if ((ret = pthread_cond_init(obj->ptr, &cond_attr))) {
      fprintf(stderr, 
          "ERROR(%s): Initializing the cv failed: %s\n",
          name, strerror(ret));
      exit(1);
    }
    if ((ret = pthread_condattr_destroy(&cond_attr))) {
      fprintf(stderr, 
          "ERROR(%s): Destruction of cond attrs failed: %s\n",
          name, strerror(ret));
      exit(1);
    }
  }
}

void shared_cond_dtor(shared_cond_t* obj) {
  if (shared_mem_isowner(obj->shm)) {
    int ret = -1;
    if ((ret = pthread_cond_destroy(obj->ptr))) {
      fprintf(stderr, "WARN: Destruction of the cv failed: %s\n",
          strerror(ret));
    }
  }
  shared_mem_dtor(obj->shm);
}

void shared_cond_wait(shared_cond_t* obj,
                      struct shared_mutex_t* mutex) {
  int ret = -1;
  if ((ret = pthread_cond_wait(obj->ptr,
                  shared_mutex_getptr(mutex)))) {
    fprintf(stderr, "ERROR: Waiting on the cv failed: %s\n",
            strerror(ret));
    exit(1);
  }
}

void shared_cond_timedwait(shared_cond_t* obj,
                           struct shared_mutex_t* mutex,
                           long int time_nanosec) {
  int ret = -1;

  struct timespec ts;
  ts.tv_sec = ts.tv_nsec = 0;
  if ((ret = clock_gettime(CLOCK_REALTIME, &ts))) {
    fprintf(stderr,
            "ERROR: Failed at reading current time: %s\n",
            strerror(errno));
    exit(1);
  }
  ts.tv_sec += (int)(time_nanosec / (1000L * 1000 * 1000));
  ts.tv_nsec += time_nanosec % (1000L * 1000 * 1000);

  if ((ret = pthread_cond_timedwait(obj->ptr,
                  shared_mutex_getptr(mutex), &ts))) {
#if !defined(__APPLE__)
    if (ret == EOWNERDEAD) {
      fprintf(stderr,
              "WARN: The owner of the cv's mutex is dead ...\n");
      shared_mutex_make_consistent(mutex);
      fprintf(stdout, "INFO: I'm the new owner!\n");
      shared_mem_setowner(obj->shm, TRUE);
      return;
    } else if (ret == ETIMEDOUT) {
#else
    if (ret == ETIMEDOUT) {
#endif
      return;
    }
    fprintf(stderr, "ERROR: Waiting on the cv failed: %s\n",
            strerror(ret));
    exit(1);
  }
}

void shared_cond_broadcast(shared_cond_t* obj) {
  int ret = -1;
  if ((ret = pthread_cond_broadcast(obj->ptr))) {
    fprintf(stderr, "ERROR: Broadcasting on the cv failed: %s\n",
        strerror(ret));
    exit(1);
  }
}
