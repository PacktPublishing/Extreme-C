// File name: ExtremeC_examples_chapter22_2.c
// Description: Definitions of the example 22.2

#include <stdlib.h>
#include <stdio.h>

#include "ExtremeC_examples_chapter22_2.h"

bool_t random_boolean() {
  int number = rand();
  return (number % 2);
}
