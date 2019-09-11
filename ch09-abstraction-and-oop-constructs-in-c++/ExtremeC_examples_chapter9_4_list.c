// File name: ExtremeC_examples_chapter9_4_list.c
// Description: Private definition of the list class

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int items[100];
  size_t size;
} list_t;

// Private constructor
void __list_ctor(list_t* list, int* items, size_t size) {
  list->size = size;
  for (size_t i = 0; i < size; i++) {
    list->items[i] = items[i];
  }
}

// Creates an empty list
list_t* list_empty() {
  list_t *list = (list_t*)malloc(sizeof(list_t));
  __list_ctor(list, NULL, 0);
  return list;
}

list_t* list_add(list_t* list, int item) {
  int *temp = (int*)malloc((list->size + 1) * sizeof(int));
  for (size_t i = 0; i < list->size; i++) {
    temp[i] = list->items[i];
  }
  temp[list->size] = item;

  // Create a new list object
  list_t *new_list = (list_t*)malloc(sizeof(list_t));
  __list_ctor(new_list, temp, list->size + 1);
  return new_list;
}

void list_print(list_t* list) {
  printf("[");
  for (size_t i = 0; i < list->size; i++) {
    printf("%d ", list->items[i]);
  }
  printf("]\n");
}
