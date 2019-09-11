// File name: ExtremeC_examples_chapter9_4_main.c
// Description: Main scenario which uses the list immutable objects

#include "ExtremeC_examples_chapter9_4_list.h"

int main(int argc, char** argv) {
  struct list_t* list1 = list_empty();
  struct list_t* list2 = list_add(list1, 23);
  struct list_t* list3 = list_add(list2, 14);
  struct list_t* list4 = list_add(list3, 10);
  list_print(list4);
  return 0;
}
