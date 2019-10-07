// File name: ExtremeC_examples_chapter22_1__next_even_number__tests.c
// Description: Test cases to test next_even_number function.

#include <assert.h>

#include "ExtremeC_examples_chapter22_1.h"

void TESTCASE_next_even_number__even_numbers_should_be_returned() {
  assert(next_even_number() == 0);
  assert(next_even_number() == 2);
  assert(next_even_number() == 4);
  assert(next_even_number() == 6);
  assert(next_even_number() == 8);
}

void TESTCASE_next_even_number__numbers_should_rotate() {
  int64_t number = next_even_number();
  next_even_number();
  next_even_number();
  next_even_number();
  next_even_number();
  int64_t number2 = next_even_number();
  assert(number == number2);
}
