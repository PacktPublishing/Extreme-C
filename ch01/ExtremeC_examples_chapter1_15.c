// File name: ExtremeC_exampels_chapter1_15.c
// Description: Example 1.15

#include <stdio.h>

int main(int argc, char** argv) {
  int var = 1;
  int* int_ptr = &var;

  printf("int_ptr: %p\n", (void*)int_ptr);

  return 0;
}
