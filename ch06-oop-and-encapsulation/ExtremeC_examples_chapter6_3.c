// File name: ExtremeC_examples_chapter6_3.c
// Description: This file contains the actual definition of
//              the `list_t` attribute structure. It also
//              contains the implementations of the behavior
//              functions exposed by the header file. It has
//              also a private behavior functions which is
//              used internally.

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

// Define the alias type bool_t
typedef int bool_t;

// Define the type list_t
typedef struct {
  size_t size;
  int* items;
} list_t;

// A private behavior which checks if list is full
bool_t __list_is_full(list_t* list) {
  return (list->size == MAX_SIZE);
}

// Another private behavior which checks the index
bool_t __check_index(list_t* list, const int index) {
  return (index >= 0 && index <= list->size);
}

// Allocates memory for a list object
list_t* list_malloc() {
  return (list_t*)malloc(sizeof(list_t));
}

// Constructor of a list object
void list_init(list_t* list) {
  list->size = 0;
  // Allocates from the heap memory
  list->items = (int*)malloc(MAX_SIZE * sizeof(int));
}

// Destructor of a list object
void list_destroy(list_t* list) {
  // Deallocates the allocated memory
  free(list->items);
}

int list_add(list_t* list, const int item) {
  // The usage of the private behavior
  if (__list_is_full(list)) {
    return -1;
  }
  list->items[list->size++] = item;
  return 0;
}

int list_get(list_t* list, const int index, int* result) {
  if (__check_index(list, index)) {
    *result = list->items[index];
    return 0;
  }
  return -1;
}

void list_clear(list_t* list) {
  list->size = 0;
}

size_t list_size(list_t* list) {
  return list->size;
}

void list_print(list_t* list) {
  printf("[");
  for (size_t i = 0; i < list->size; i++) {
    printf("%d ", list->items[i]);
  }
  printf("]\n");
}
