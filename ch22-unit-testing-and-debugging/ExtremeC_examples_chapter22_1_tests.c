// File name: ExtremeC_examples_chapter22_1_tests.c
// Description: The main function which runs the tests

#include <stdio.h>

void TESTCASE_next_even_number__even_numbers_should_be_returned();
void TESTCASE_next_even_number__numbers_should_rotate();

void TESTCASE_calc_factorial__fact_of_zero_is_one();
void TESTCASE_calc_factorial__fact_of_negative_is_one();
void TESTCASE_calc_factorial__fact_of_5_is_120();

int main(int argc, char** argv) {
  TESTCASE_next_even_number__even_numbers_should_be_returned();
  TESTCASE_next_even_number__numbers_should_rotate();
  TESTCASE_calc_factorial__fact_of_zero_is_one();
  TESTCASE_calc_factorial__fact_of_negative_is_one();
  TESTCASE_calc_factorial__fact_of_5_is_120();
  printf("All tests are run successfully.\n");
  return 0;
}
