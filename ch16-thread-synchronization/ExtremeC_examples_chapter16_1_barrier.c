// File name: ExtremeC_examples_chapter16_1_barrier.c
// Description: This example demonstrates how to use barriers
//              to synchronize two threads.

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

// The barrier object
pthread_barrier_t barrier;

void* thread_body_1(void* arg) {
  printf("A\n");
  // Wait for the other thread to join
  pthread_barrier_wait(&barrier);
  return NULL;
}

void* thread_body_2(void* arg) {
  // Wait for the other thread to join
  pthread_barrier_wait(&barrier);
  printf("B\n");
  return NULL;
}

int main(int argc, char** argv) {

  // Initialize the barrier object
  pthread_barrier_init(&barrier, NULL, 2);

  // The thread handlers
  pthread_t thread1;
  pthread_t thread2;

  // Create new threads
  int result1 = pthread_create(&thread1, NULL,
          thread_body_1, NULL);
  int result2 = pthread_create(&thread2, NULL,
          thread_body_2, NULL);

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

  // Destroy the barrier object
  pthread_barrier_destroy(&barrier);

  return 0;
}
