// File name: ExtremeC_exampels_chapter1_18.c
// Description: Example 1.18

#include <stdio.h>

void func(int* a) {
  int b = 9;
  *a = 5;
  a = &b;
}

int main(int argc, char** argv) {
  int x = 3;
  int* xptr = &x;
  printf("Value before call: %d\n", x);
  printf("Pointer before function call: %p\n", (void*)xptr);
  func(xptr);
  printf("Value after call: %d\n", x);
  printf("Pointer after function call: %p\n", (void*)xptr);
  return 0;
}
