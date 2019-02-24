// File name: ExtremeC_examples_chapter19_1_tests.c
// Description: Test cases to test calc_factorial function.

#include <assert.h>

#include "ExtremeC_examples_chapter19_1.h"

int64_t fake_value = -1;

int64_t fake_feed() {
  return fake_value;
}

void TESTCASE_calc_factorial__fact_of_zero_is_one() {
  fake_value = 0;
  int64_t fact = calc_factorial(fake_feed);
  assert(fact == 1);
}

void TESTCASE_calc_factorial__fact_of_negative_is_one() {
  fake_value = -10;
  int64_t fact = calc_factorial(fake_feed);
  assert(fact == 1);
}

void TESTCASE_calc_factorial__fact_of_5_is_120() {
  fake_value = 5;
  int64_t fact = calc_factorial(fake_feed);
  assert(fact == 120);
}
