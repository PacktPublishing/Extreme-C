// File name: ExtremeC_examples_chapter2_5_main.c
// Description: This file contains the 'main' function and a definition for another function 'add'.

#include <stdio.h>

int add(int, int);

int main(int argc, char** argv) {
  int x = add(5, 6);
  printf("Result: %d\n", x);
  return 0;
}
