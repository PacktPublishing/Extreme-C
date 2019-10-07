// File name: ExtremeC_examples_chapter22_1_component_tests.c
// Description: Demosntrates how to write component test
//              for the example 22.1

#include <assert.h>

#include "ExtremeC_examples_chapter22_1.h"

void TESTCASE_component_test__factorials_from_0_to_8() {
  assert(calc_factorial(next_even_number) == 1);
  assert(calc_factorial(next_even_number) == 2);
  assert(calc_factorial(next_even_number) == 24);
  assert(calc_factorial(next_even_number) == 720);
  assert(calc_factorial(next_even_number) == 40320);
}

void TESTCASE_component_test__factorials_should_rotate() {
  int64_t number = calc_factorial(next_even_number);
  for (size_t i = 1; i <= 4; i++) {
    calc_factorial(next_even_number);
  }
  int64_t number2 = calc_factorial(next_even_number);
  assert(number == number2);
}

int main(int argc, char** argv) {
  TESTCASE_component_test__factorials_from_0_to_8();
  TESTCASE_component_test__factorials_should_rotate();
  return 0;
}
