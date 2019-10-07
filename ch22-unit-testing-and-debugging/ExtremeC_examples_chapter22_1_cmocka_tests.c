// File name: ExtremeC_examples_chapter22_1_cmocka_tests.c
// Description: CMocka test cases for the example 22.1.

// Required by CMocka
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "ExtremeC_examples_chapter22_1.h"

int64_t input_value = -1;

int64_t feed_stub() {
  return input_value;
}

void calc_factorial__fact_of_zero_is_one(void** state) {
  input_value = 0;
  int64_t fact = calc_factorial(feed_stub);
  assert_int_equal(fact, 1);
}

void calc_factorial__fact_of_negative_is_one(void** state) {
  input_value = -10;
  int64_t fact = calc_factorial(feed_stub);
  assert_int_equal(fact, 1);
}

void calc_factorial__fact_of_5_is_120(void** state) {
  input_value = 5;
  int64_t fact = calc_factorial(feed_stub);
  assert_int_equal(fact, 120);
}

void next_even_number__even_numbers_should_be_returned(void** state) {
  assert_int_equal(next_even_number(), 0);
  assert_int_equal(next_even_number(), 2);
  assert_int_equal(next_even_number(), 4);
  assert_int_equal(next_even_number(), 6);
  assert_int_equal(next_even_number(), 8);
}

void next_even_number__numbers_should_rotate(void** state) {
  int64_t number = next_even_number();
  for (size_t i = 1; i <= 4; i++) {
    next_even_number();
  }
  int64_t number2 = next_even_number();
  assert_int_equal(number, number2);
}

int setup(void** state) {
  return 0;
}

int tear_down(void** state) {
  return 0;
}

int main(int argc, char** argv) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(calc_factorial__fact_of_zero_is_one),
    cmocka_unit_test(calc_factorial__fact_of_negative_is_one),
    cmocka_unit_test(calc_factorial__fact_of_5_is_120),
    cmocka_unit_test(next_even_number__even_numbers_should_be_returned),
    cmocka_unit_test(next_even_number__numbers_should_rotate),
  };
  return cmocka_run_group_tests(tests, setup, tear_down);
}
