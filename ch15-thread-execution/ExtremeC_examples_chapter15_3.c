// File name: ExtremeC_examples_chapter10_3.c
// Description: This example creates two threads which try
//              to read and modify a single shared variable
//              at the same time.

#include <stdio.h>
#include <stdlib.h>

// The POSIX standard header for using pthread library
#include <pthread.h>

void* thread_body_1(void* arg) {
  // Obtain a pointer to the shared variable
  int* shared_var_ptr = (int*)arg;
  // Increment the shared variable by 1 by writing
  // directly to its memory address
  (*shared_var_ptr)++;
  printf("%d\n", *shared_var_ptr);
  return NULL;
}

void* thread_body_2(void* arg) {
  // Obtain a pointer to the shared variable
  int* shared_var_ptr = (int*)arg;
  // Increment the shared variable by 2 by writing
  // directly to its memory address
  *shared_var_ptr += 2;
  printf("%d\n", *shared_var_ptr);
  return NULL;
}

int main(int argc, char** argv) {

  // The shared variable
  int shared_var = 0;

  // The thread handlers
  pthread_t thread1;
  pthread_t thread2;

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
  return 0;
}
