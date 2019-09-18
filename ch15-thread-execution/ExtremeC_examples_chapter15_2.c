// File name: ExtremeC_examples_chapter10_2.c
// Description: This example creates three threads which
//              print different strings. Different interleavings
//              imposed by the scheduler lead to different
//              outputs in this example.

#include <stdio.h>
#include <stdlib.h>

// The POSIX standard header for using pthread library
#include <pthread.h>

void* thread_body(void* arg) {
  char* str = (char*)arg;
  printf("%s\n", str);
  return NULL;
}

int main(int argc, char** argv) {

  // The thread handlers
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;

  // Create new threads
  int result1 = pthread_create(&thread1, NULL,
          thread_body, "Apple");
  int result2 = pthread_create(&thread2, NULL,
          thread_body, "Orange");
  int result3 = pthread_create(&thread3, NULL,
          thread_body, "Lemon");

  if (result1 || result2 || result3) {
    printf("The threads could not be created.\n");
    exit(1);
  }

  // Wait for the threads to finish
  result1 = pthread_join(thread1, NULL);
  result2 = pthread_join(thread2, NULL);
  result3 = pthread_join(thread3, NULL);

  if (result1 || result2 || result3) {
    printf("The threads could not be joined.\n");
    exit(2);
  }
  return 0;
}
