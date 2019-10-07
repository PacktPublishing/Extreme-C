// File name: ExtremeC_examples_chapter22_2_cmocka_tests_with_stub.c
// Description: CMocka test cases for the exmaple 22.2
//              using a stub function.

#include <stdlib.h>

// Required by CMocka
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "ExtremeC_examples_chapter22_2.h"

int next_random_num = 0;

int __wrap_rand() {
  return next_random_num;
}

void test_even_random_number(void** state) {
  next_random_num = 10;
  assert_false(random_boolean());
}

void test_odd_random_number(void** state) {
  next_random_num = 13;
  assert_true(random_boolean());
}
int main(int argc, char** argv) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_even_random_number),
    cmocka_unit_test(test_odd_random_number)
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
