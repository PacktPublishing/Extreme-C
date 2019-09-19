// File name: ExtremeC_examples_chapter16_6.c
// Description: This example shows how to use recursive mutexes.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h> // The POSIX standard header for using pthread library

#define TRUE 1
#define FALSE 0

typedef unsigned int bool_t;

typedef struct {
  double* items;
  size_t size;
  size_t max_size;
  pthread_mutex_t mtx;
} my_stack_t;

void my_stack_ctor(my_stack_t* my_stack) {
  my_stack->max_size = 10;
  my_stack->items = (double*)malloc(my_stack->max_size * sizeof(double));
  my_stack->size = 0;

  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&my_stack->mtx, &attr);
}

void my_stack_dtor(my_stack_t* my_stack) {
  free(my_stack->items);
  pthread_mutex_destroy(&my_stack->mtx);
}

bool_t my_stack_full(my_stack_t* my_stack) {
  pthread_mutex_lock(&my_stack->mtx);
  bool_t result = (my_stack->size >= my_stack->max_size) ? TRUE : FALSE;
  pthread_mutex_unlock(&my_stack->mtx);
  return result;
}

bool_t my_stack_empty(my_stack_t* my_stack) {
  pthread_mutex_lock(&my_stack->mtx);
  bool_t result = (my_stack->size == 0) ? TRUE : FALSE;
  pthread_mutex_unlock(&my_stack->mtx);
  return result;
}

bool_t my_stack_push(my_stack_t* my_stack, double item) {
  pthread_mutex_lock(&my_stack->mtx);
  if (my_stack_full(my_stack)) {
    pthread_mutex_unlock(&my_stack->mtx);
    return FALSE;
  }
  my_stack->items[my_stack->size] = item;
  my_stack->size++;
  pthread_mutex_unlock(&my_stack->mtx);
  return TRUE;
}

bool_t my_stack_pop(my_stack_t* my_stack, double* result) {
  pthread_mutex_lock(&my_stack->mtx);
  if (my_stack_empty(my_stack)) {
    pthread_mutex_unlock(&my_stack->mtx);
    return FALSE;
  }
  *result = my_stack->items[my_stack->size - 1];
  my_stack->size--;
  pthread_mutex_unlock(&my_stack->mtx);
  return TRUE;
}

my_stack_t shared_stack;

void* pusher_thread_body(void* arg) {
  while (TRUE) {
    if (!my_stack_full(&shared_stack)) {
      double to_push = 10.0;
      if (my_stack_push(&shared_stack, to_push)) {
        printf ("Pushed: %f\n", to_push);
      }
    }
  }
  return NULL;
}

void* popper_thread_body(void* arg) {
  while (TRUE) {
    if (!my_stack_empty(&shared_stack)) {
      double result = 0.0;
      if (my_stack_pop(&shared_stack, &result)) {
        printf("Popped: %f\n", result);
      }
    }
  }
  return NULL;
}

int main(int argc, char** argv) {

  my_stack_ctor(&shared_stack);

  pthread_t pusher_thread;
  pthread_t popper_thread;

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  if (pthread_create(&pusher_thread, &attr, pusher_thread_body, NULL)) {
    printf("Couldn't create the pusher thread.\n");
    exit(1);
  }

  if (pthread_create(&popper_thread, &attr, popper_thread_body, NULL)) {
    printf("Couldn't create the popper thread.\n");
    exit(2);
  }

  pthread_exit(NULL);

  return 0;
}
