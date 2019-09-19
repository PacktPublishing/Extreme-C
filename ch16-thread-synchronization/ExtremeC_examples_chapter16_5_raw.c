// File name: ExtremeC_examples_chapter16_5_raw.c
// Description: This example is about five threads manipulating
//              a heap allocated shared array. In this code, no
//              control mechanism is employed.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#define CHECK_RESULT(result) \
if (result) { \
  printf("A pthread error happened.\n"); \
  exit(1); \
}

int TRUE = 1;
int FALSE = 0;

// The pointer to the shared array
char* shared_array;
// The size of the shared array
unsigned int shared_array_len;

void* alloc_thread_body(void* arg) {
  shared_array_len = 20;
  shared_array = (char*)malloc(shared_array_len * sizeof(char*));
  return NULL;
}

void* filler_thread_body(void* arg) {
  int even = *((int*)arg);
  char c = 'a';
  size_t start_index = 1;
  if (even) {
    c = 'Z';
    start_index = 0;
  }
  for (size_t i = start_index; i < shared_array_len; i += 2) {
    shared_array[i] = even ? c-- : c++;
  }
  shared_array[shared_array_len - 1] = '\0';
  return NULL;
}

void* printer_thread_body(void* arg) {
  printf(">> %s\n", shared_array);
  return NULL;
}

void* dealloc_thread_body(void* arg) {
  free(shared_array);
  return NULL;
}

int main(int argc, char** argv) {

  shared_array = NULL;

  pthread_t alloc_thread;
  pthread_t even_filler_thread;
  pthread_t odd_filler_thread;
  pthread_t printer_thread;
  pthread_t dealloc_thread;

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  int res = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  CHECK_RESULT(res);

  res = pthread_create(&alloc_thread, &attr, alloc_thread_body, NULL);
  CHECK_RESULT(res);

  res = pthread_create(&even_filler_thread,
          &attr, filler_thread_body, &TRUE);
  CHECK_RESULT(res);

  res = pthread_create(&odd_filler_thread,
          &attr, filler_thread_body, &FALSE);
  CHECK_RESULT(res);

  res = pthread_create(&printer_thread, &attr, printer_thread_body, NULL);
  CHECK_RESULT(res);

  res = pthread_create(&dealloc_thread, &attr, dealloc_thread_body, NULL);
  CHECK_RESULT(res);

  pthread_exit(NULL);

  return 0;
}
