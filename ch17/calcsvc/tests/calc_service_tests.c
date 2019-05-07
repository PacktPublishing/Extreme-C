#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <calc_service.h>

#define EPSILON 0.000001

struct calc_service_t* svc = NULL;

void calc_service__add_without_memory(void** state) {
  calc_service_ctor(svc);
  calc_service_reset_mem(svc);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
  double result = calc_service_add(svc, 3.4, -9.8, FALSE);
  assert_float_equal(result, -6.4, EPSILON);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
}

void calc_service__add_with_memory(void** state) {
  calc_service_ctor(svc);
  calc_service_reset_mem(svc);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
  double result = calc_service_add(svc, 3.4, -9.8, TRUE);
  assert_float_equal(result, -6.4, EPSILON);
  assert_float_equal(calc_service_get_mem(svc), -6.4, EPSILON);
  result = calc_service_add(svc, 3.4, 2.0, TRUE);
  assert_float_equal(result, -1.0, EPSILON);
  assert_float_equal(calc_service_get_mem(svc), -1.0, EPSILON);
}

void calc_service__sub_without_memory(void** state) {
  calc_service_ctor(svc);
  calc_service_reset_mem(svc);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
  double result = calc_service_sub(svc, 3.4, -1.2, FALSE);
  assert_float_equal(result, 4.6, EPSILON);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
}

void calc_service__sub_with_memory(void** state) {
  calc_service_ctor(svc);
  calc_service_reset_mem(svc);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
  double result = calc_service_sub(svc, 3.4, -1.2, TRUE);
  assert_float_equal(result, 4.6, EPSILON);
  assert_float_equal(calc_service_get_mem(svc), 4.6, EPSILON);
  result = calc_service_sub(svc, 3.4, 2.4, TRUE);
  assert_float_equal(result, -3.6, EPSILON);
  assert_float_equal(calc_service_get_mem(svc), -3.6, EPSILON);
}

void calc_service__mul_without_memory(void** state) {
  calc_service_ctor(svc);
  calc_service_reset_mem(svc);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
  double result = calc_service_mul(svc, 2.67, -6.45, FALSE);
  assert_float_equal(result, -17.2215, EPSILON);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
}

void calc_service__mul_with_memory(void** state) {
  calc_service_ctor(svc);
  calc_service_reset_mem(svc);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
  double result = calc_service_mul(svc, 2.67, -6.45, TRUE);
  assert_float_equal(result, 0.0, EPSILON);
  assert_float_equal(calc_service_get_mem(svc), 0.0, EPSILON);
  result = calc_service_add(svc, 1.5, 0.0, TRUE);
  assert_float_equal(result, 1.5, EPSILON);
  assert_float_equal(calc_service_get_mem(svc), 1.5, EPSILON);
  result = calc_service_mul(svc, 1.6, 2.4, TRUE);
  assert_float_equal(result, 5.76, EPSILON);
  assert_float_equal(calc_service_get_mem(svc), 5.76, EPSILON);
}

void calc_service__div(void** state) {
  calc_service_ctor(svc);
  calc_service_reset_mem(svc);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
  double result = 0.0;
  int status = calc_service_div(svc, -7.81, -2.3, &result);
  assert_int_equal(status, CALC_SVC_OK);
  assert_float_equal(result, 3.395652 , EPSILON);
  assert_float_equal(0.0, calc_service_get_mem(svc), EPSILON);
}

void calc_service__div_by_zero(void** state) {
  calc_service_ctor(svc);
  double result = 0.0;
  int status = calc_service_div(svc, -7.81, 0.0, &result);
  assert_int_equal(status, CALC_SVC_ERROR_DIV_BY_ZERO);
  assert_float_equal(result, 0.0, EPSILON);
}

int setup(void** state) {
  svc =  calc_service_new();
  return 0;
}

int teardown(void** state) {
  calc_service_dtor(svc);
  calc_service_delete(svc);
  return 0;
}

int main(int argc, char** argv) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test_setup_teardown(calc_service__add_without_memory, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_service__add_with_memory, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_service__sub_without_memory, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_service__sub_with_memory, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_service__mul_without_memory, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_service__mul_with_memory, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_service__div, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_service__div_by_zero, setup, teardown)
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
