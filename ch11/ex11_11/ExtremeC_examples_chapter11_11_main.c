// File name: ExtremeC_examples_chapter11_11_main.c
// Description: The example 11.11's main logic.

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "ExtremeC_examples_chapter11_11_shared_int32.h"
#include "ExtremeC_examples_chapter11_11_shared_mutex.h"
#include "ExtremeC_examples_chapter11_11_shared_cond.h"

int int_received = 0;
struct shared_cond_t* cond = NULL;
struct shared_mutex_t* mutex = NULL;

void sigint_handler(int signo) {
  fprintf(stdout, "\nHandling INT signal: %d ...\n", signo);
  int_received = 1;
  shared_mutex_lock(mutex);
  shared_cond_broadcast(cond);
  shared_mutex_unlock(mutex);
}

int main(int argc, char** argv) {

  signal(SIGINT, sigint_handler);

  int my_number = atol(argv[1]);
  printf("My number is %d!\n", my_number);

  struct shared_int32_t* counter = shared_int32_new();
  shared_int32_ctor(counter, "/counter0");
  shared_int32_setvalue_ifowner(counter, 1);

  mutex = shared_mutex_new();
  shared_mutex_ctor(mutex, "/mutex0");

  cond = shared_cond_new();
  shared_cond_ctor(cond, "/cond0");

  shared_mutex_lock(mutex);
  while (shared_int32_getvalue(counter) < my_number &&
	       !int_received) { 
    printf("Waiting for my trun ...\n");
    shared_cond_wait(cond, mutex);
    printf("Checking condition ...\n");
  }
  if (int_received) {
    printf("Exiting ...\n");
    shared_mutex_unlock(mutex);
    goto destroy;
  }
  printf("My turn! %d ...\n", my_number);
  shared_int32_setvalue(counter, my_number + 1);
  shared_cond_broadcast(cond);
  shared_mutex_unlock(mutex);
  
destroy:
  shared_cond_dtor(cond);
  shared_cond_delete(cond);

  shared_mutex_dtor(mutex);
  shared_mutex_delete(mutex);

  shared_int32_dtor(counter);
  shared_int32_delete(counter);

  return 0;
}
