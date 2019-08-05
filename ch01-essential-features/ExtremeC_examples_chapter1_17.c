// File name: ExtremeC_exampels_chapter1_17.c
// Description: Example 1.17

#include <stdio.h>

void func(int a) {
  a = 5;
}

int main(int argc, char** argv) {
  int x = 3;
  printf("Before function call: %d\n", x);
  func(x);
  printf("After function call: %d\n", x);
  return 0;
}
