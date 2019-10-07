// File name: ExtremeC_examples_chapter22_1__calc_factorial__tests.c
// Description: Test cases to test calc_factorial function.

#include <assert.h>

#include "ExtremeC_examples_chapter22_1.h"

int64_t input_value = -1;

int64_t feed_stub() {
  return input_value;
}

void TESTCASE_calc_factorial__fact_of_zero_is_one() {
  input_value = 0;
  int64_t fact = calc_factorial(feed_stub);
  assert(fact == 1);
}

void TESTCASE_calc_factorial__fact_of_negative_is_one() {
  input_value = -10;
  int64_t fact = calc_factorial(feed_stub);
  assert(fact == 1);
}

void TESTCASE_calc_factorial__fact_of_5_is_120() {
  input_value = 5;
  int64_t fact = calc_factorial(feed_stub);
  assert(fact == 120);
}
