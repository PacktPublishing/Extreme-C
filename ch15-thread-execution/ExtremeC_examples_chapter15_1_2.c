// File name: ExtremeC_examples_chapter10_1_2.c
// Description: Example 6.1 using detached threads.

#include <stdio.h>
#include <stdlib.h>

// The POSIX standard header for using pthread library
#include <pthread.h>

// This function contains the logic which should be run
// as the body of a separate thread
void* thread_body(void* arg) {
  printf("Hello from first thread!\n");
  return NULL;
}

int main(int argc, char** argv) {

  // The thread handler
  pthread_t thread;

  // Create a new thread
  int result = pthread_create(&thread, NULL, thread_body, NULL);
  // If the thread creation did not succeed
  if (result) {
    printf("Thread could not be created. Error number: %d\n",
            result);
    exit(1);
  }

  // Detach the thread
  result = pthread_detach(thread);
  // If detaching the thread did not succeed
  if (result) {
    printf("Thread could not be detached. Error number: %d\n",
            result);
    exit(2);
  }

  // Exit the main thread
  pthread_exit(NULL);

  return 0;
}
