// File name: ExtremeC_examples_chapter10_1.c
// Description: Start a thread which performs a simple task!

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

  // Wait for the created thread to finish
  result = pthread_join(thread, NULL);
  // If joining the thread did not succeed
  if (result) {
    printf("The thread could not be joined. Error number: %d\n",
            result);
    exit(2);
  }
  return 0;
}
