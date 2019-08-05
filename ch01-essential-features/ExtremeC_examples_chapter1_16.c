// File name: ExtremeC_exampels_chapter1_16.c
// Description: Example 1.16

#include <stdio.h>
#include <stdlib.h>

int* create_an_integer(int default_value) {
  int* var_ptr = (int*)malloc(sizeof(int));
  *var_ptr = default_value;
  return var_ptr;
}

int main() {
  int* ptr = NULL;
  ptr = create_an_integer(10);
  printf("%d\n", *ptr);
  free(ptr);
  return 0;
}
