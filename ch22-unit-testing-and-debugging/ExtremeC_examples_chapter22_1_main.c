// File name: ExtremeC_examples_chapter22_1_main.c
// Description: Main logic using the declared functions

#include <stdio.h>

#include "ExtremeC_examples_chapter22_1.h"

int main(int argc, char** argv) {
  for (size_t i = 1; i <= 12; i++) {
    printf("%lu\n", calc_factorial(next_even_number));
  }
  return 0;
}
