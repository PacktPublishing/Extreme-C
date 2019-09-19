// File name: ExtremeC_examples_chapter15_3_mutex.c
// Description: This example uses a mutex to resolve the
//              data race issue observed in the example 15.3.

#include <stdio.h>
#include <stdlib.h>

// The POSIX standard header for using pthread library
#include <pthread.h>

// The mutex object used to synchronize the access to
// the shared state.
pthread_mutex_t mtx;

void* thread_body_1(void* arg) {
  // Obtain a pointer to the shared variable
  int* shared_var_ptr = (int*)arg;

  // Critical section
  pthread_mutex_lock(&mtx);
  (*shared_var_ptr)++;
  printf("%d\n", *shared_var_ptr);
  pthread_mutex_unlock(&mtx);

  return NULL;
}

void* thread_body_2(void* arg) {
  int* shared_var_ptr = (int*)arg;

  // Critical section
  pthread_mutex_lock(&mtx);
  *shared_var_ptr += 2;
  printf("%d\n", *shared_var_ptr);
  pthread_mutex_unlock(&mtx);

  return NULL;
}

int main(int argc, char** argv) {

  // The shared variable
  int shared_var = 0;

  // The thread handlers
  pthread_t thread1;
  pthread_t thread2;

  // Initiliaze the mutex and its underlying resources
  pthread_mutex_init(&mtx, NULL);

  // Create new threads
  int result1 = pthread_create(&thread1, NULL,
          thread_body_1, &shared_var);
  int result2 = pthread_create(&thread2, NULL,
          thread_body_2, &shared_var);

  if (result1 || result2) {
    printf("The threads could not be created.\n");
    exit(1);
  }

  // Wait for the threads to finish
  result1 = pthread_join(thread1, NULL);
  result2 = pthread_join(thread2, NULL);

  if (result1 || result2) {
    printf("The threads could not be joined.\n");
    exit(2);
  }

  pthread_mutex_destroy(&mtx);

  return 0;
}
