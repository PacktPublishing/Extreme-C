// File name: ExtremeC_examples_chapter16_3.c
// Description: This example shows how to set the stack
//              size and the satck address of a new thread.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <pthread.h>

void* thread_body_1(void* arg) {
  int local_var = 0;
  printf("Thread1 > Stack Address: %p\n", (void*)&local_var);
  return 0;
}

void* thread_body_2(void* arg) {
  int local_var = 0;
  printf("Thread2 > Stack Address: %p\n", (void*)&local_var);
  return 0;
}

int main(int argc, char** argv) {

  size_t buffer_len = PTHREAD_STACK_MIN + 100;
  // The buffer allocated from heap to be used as
  // the thread's stack region
  char *buffer = (char*)malloc(buffer_len * sizeof(char));

  // The thread handlers
  pthread_t thread1;
  pthread_t thread2;

  // Create a new thread with default attributes
  int result1 = pthread_create(&thread1, NULL,
          thread_body_1, NULL);

  // Create a new thread with a custom stack region
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  // Set the stack address and size
  if (pthread_attr_setstack(&attr, buffer, buffer_len)) {
    printf("Failed while setting the stack attributes.\n");
    exit(1);
  }
  int result2 = pthread_create(&thread2, &attr,
          thread_body_2, NULL);

  if (result1 || result2) {
    printf("The threads could not be created.\n");
    exit(2);
  }

  printf("Main Thread > Heap Address: %p\n", (void*)buffer);
  printf("Main Thread > Stack Address: %p\n", (void*)&buffer_len);

  // Wait for the threads to finish
  result1 = pthread_join(thread1, NULL);
  result2 = pthread_join(thread2, NULL);

  if (result1 || result2) {
    printf("The threads could not be joined.\n");
    exit(3);
  }

  free(buffer);

  return 0;
}
