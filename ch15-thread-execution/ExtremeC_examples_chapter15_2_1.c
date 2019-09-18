// File name: ExtremeC_examples_chapter10_2_1.c
// Description: This code is the same as the code written
//              for the example 10.2 but this time, we want
//              to have some dangling pointers passed to
//              the threads instead of pointers to the
//              string literals

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  char str1[8], str2[8], str3[8];
  strcpy(str1, "Apple");
  strcpy(str2, "Orange");
  strcpy(str3, "Lemon");

  // Create new threads
  int result1 = pthread_create(&thread1, NULL, thread_body, str1);
  int result2 = pthread_create(&thread2, NULL, thread_body, str2);
  int result3 = pthread_create(&thread3, NULL, thread_body, str3);

  if (result1 || result2 || result3) {
    printf("The threads could not be created.\n");
    exit(1);
  }

  // Detach the threads
  result1 = pthread_detach(thread1);
  result2 = pthread_detach(thread2);
  result3 = pthread_detach(thread3);

  if (result1 || result2 || result3) {
    printf("The threads could not be detached.\n");
    exit(2);
  }

  // Now, the strings become deallocated.
  pthread_exit(NULL);

  return 0;
}
