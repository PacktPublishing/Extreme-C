#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <calc_proto_ser.h>

#define TRUE 1
#define FALSE 0

typedef int bool_t;

int expected_error_code;
int expected_status;

bool_t err_cb_called;
bool_t req_cb_called;
bool_t resp_cb_called;

struct calc_proto_ser_t* ser = NULL;

void req_cb(void* context, struct calc_proto_req_t req) {
  req_cb_called = TRUE;
  assert_int_equal(req.id, 1300);
  assert_int_equal(req.method, GETMEM);
  assert_float_equal(req.operand1, -12.302, 0.01);
  assert_float_equal(req.operand2, 45.3, 0.01);
}

void resp_cb(void* context, struct calc_proto_resp_t resp) {
  resp_cb_called = TRUE;
  assert_int_equal(resp.req_id, 1245);
  assert_int_equal(resp.status, expected_status);
  assert_float_equal(resp.result, -104.891, 0.01);
}

void error_cb(void* context, int ref_id, int error_code) {
  err_cb_called = TRUE;
  assert_int_equal(error_code, expected_error_code);
}

void calc_server_deserialize__long_request(void** state) {
  calc_proto_ser_ctor(ser, NULL, 10);
  char req[] = "1300#GETMEM#12.3#45.3$";
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_REQUEST;
  calc_proto_ser_server_deserialize(ser, buf, NULL);
  assert_true(err_cb_called);
}

void calc_server_deserialize__long_request_2(void** state) {
  calc_proto_ser_ctor(ser, NULL, 10);
  char part1[] = "1300#";
  char part2[] = "GETMEM#";
  char part3[] = "12.3#";
  char part4[] = "45.3";
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_REQUEST;

  buf.data = part1;
  buf.len = strlen(part1);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = part2;
  buf.len = strlen(part2);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = part3;
  buf.len = strlen(part3);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = part4;
  buf.len = strlen(part4);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  assert_true(err_cb_called);
}

void calc_server_deserialize__invalid_method(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char req[] = "1300#INVALID#12.3#45.3$";
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_REQUEST_METHOD;
  calc_proto_ser_server_deserialize(ser, buf, NULL);
  assert_true(err_cb_called);
}

void calc_server_deserialize__invalid_operand(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char req[] = "1300#GETMEM#hello#45.3$";
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_REQUEST_OPERAND1;
  calc_proto_ser_server_deserialize(ser, buf, NULL);
  assert_true(err_cb_called);
}

void calc_server_deserialize__invalid_operand_2(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char req[] = "1300#GETMEM#12.3#hello$";
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_REQUEST_OPERAND2;
  calc_proto_ser_server_deserialize(ser, buf, NULL);
  assert_true(err_cb_called);
}

void calc_server_deserialize__too_many_fields(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char req[] = "1300#GETMEM#12.3#34.5#-2.4$";
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_REQUEST;
  calc_proto_ser_server_deserialize(ser, buf, NULL);
  assert_true(err_cb_called);
}

void calc_server_deserialize__single_request(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char req[] = "1300#GETMEM#-12.302#45.3$";
  calc_proto_ser_set_req_callback(ser, req_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  req_cb_called = FALSE;
  calc_proto_ser_server_deserialize(ser, buf, NULL);
  assert_true(err_cb_called);
}

void calc_server_deserialize__multipart_request(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char part1[] = "1300#";
  char part2[] = "GETM";
  char part3[] = "EM#-12.302#";
  char part4[] = "45.3$";
  calc_proto_ser_set_req_callback(ser, req_cb);
  struct buffer_t buf;
  req_cb_called = FALSE;

  buf.data = part1;
  buf.len = strlen(part1);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = part2;
  buf.len = strlen(part2);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = part3;
  buf.len = strlen(part3);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = part4;
  buf.len = strlen(part4);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  assert_true(req_cb_called);
}

void calc_server_deserialize__multipart_request_2(void** state) {
  calc_proto_ser_ctor(ser, NULL, 40);
  char part1[] = "130";
  char part2[] = "0#GETMEM#";
  char part3[] = "-12.302#";
  char part4[] = "45.3$";
  calc_proto_ser_set_req_callback(ser, req_cb);
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;

  req_cb_called = FALSE;
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_REQUEST;

  buf.data = part1;
  buf.len = strlen(part1);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = part2;
  buf.len = strlen(part2);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = "$";
  buf.len = 1;
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  assert_true(err_cb_called);

  buf.data = part1;
  buf.len = strlen(part1);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = part2;
  buf.len = strlen(part2);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = part3;
  buf.len = strlen(part3);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  buf.data = part4;
  buf.len = strlen(part4);
  calc_proto_ser_server_deserialize(ser, buf, NULL);

  assert_true(req_cb_called);
}

void calc_client_deserialize__invalid_req_id(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char req[] = "hello#2#-104.891$";
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_RESPONSE_REQ_ID;
  calc_proto_ser_client_deserialize(ser, buf, NULL);
  assert_true(err_cb_called);
}

void calc_client_deserialize__invalid_status(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char req[] = "1245#hello#-104.891$";
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_RESPONSE_STATUS;
  calc_proto_ser_client_deserialize(ser, buf, NULL);
  assert_true(err_cb_called);
}

void calc_client_deserialize__invalid_status_2(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char req[] = "1245#5#-104.891$";
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_RESPONSE_STATUS;
  calc_proto_ser_client_deserialize(ser, buf, NULL);
  assert_true(err_cb_called);
}

void calc_client_deserialize__invalid_result(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char req[] = "1245#4#hello$";
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_RESPONSE_RESULT;
  calc_proto_ser_client_deserialize(ser, buf, NULL);
  assert_true(err_cb_called);
}

void calc_client_deserialize__single_response(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char req[] = "1245#4#-104.891$";
  calc_proto_ser_set_resp_callback(ser, resp_cb);
  struct buffer_t buf;
  buf.data = req;
  buf.len = strlen(req);
  resp_cb_called = FALSE;
  expected_status = STATUS_DIV_BY_ZERO;
  calc_proto_ser_client_deserialize(ser, buf, NULL);
  assert_true(resp_cb_called);
}

void calc_client_deserialize__multipart_request_2(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  char part1[] = "124";
  char part2[] = "5#1#";
  char part3[] = "-104.891$";
  calc_proto_ser_set_resp_callback(ser, resp_cb);
  calc_proto_ser_set_error_callback(ser, error_cb);
  struct buffer_t buf;

  resp_cb_called = FALSE;
  err_cb_called = FALSE;
  expected_error_code = ERROR_INVALID_RESPONSE_RESULT;

  buf.data = part1;
  buf.len = strlen(part1);
  calc_proto_ser_client_deserialize(ser, buf, NULL);

  buf.data = part2;
  buf.len = strlen(part2);
  calc_proto_ser_client_deserialize(ser, buf, NULL);

  buf.data = "$";
  buf.len = 1;
  calc_proto_ser_client_deserialize(ser, buf, NULL);

  assert_true(err_cb_called);

  expected_status = STATUS_INVALID_REQUEST;

  buf.data = part1;
  buf.len = strlen(part1);
  calc_proto_ser_client_deserialize(ser, buf, NULL);

  buf.data = part2;
  buf.len = strlen(part2);
  calc_proto_ser_client_deserialize(ser, buf, NULL);

  buf.data = part3;
  buf.len = strlen(part3);
  calc_proto_ser_client_deserialize(ser, buf, NULL);

  assert_true(resp_cb_called);
}


void calc_server_serialize_response(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  struct calc_proto_resp_t resp;
  resp.req_id = 153;
  resp.status = STATUS_INVALID_METHOD;
  resp.result = -90.5613;
  struct buffer_t buf = calc_proto_ser_server_serialize(ser, &resp);
  assert_string_equal(buf.data, "153#2#-90.5613$");
  free(buf.data);
}

void calc_client_serialize_request(void** state) {
  calc_proto_ser_ctor(ser, NULL, 32);
  struct calc_proto_req_t req;
  req.id = 153;
  req.method = SUBM;
  req.operand1 = 102.34;
  req.operand2 = -3.4409;
  struct buffer_t buf = calc_proto_ser_client_serialize(ser, &req);
  assert_string_equal(buf.data, "153#SUBM#102.34#-3.4409$");
  free(buf.data);
}

int setup(void** state) {
  ser = calc_proto_ser_new();
  return 0;
}

int teardown(void** state) {
  calc_proto_ser_dtor(ser);
  calc_proto_ser_delete(ser);
  return 0;
}

int main(int argc, char** argv) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test_setup_teardown(calc_server_deserialize__long_request, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_server_deserialize__long_request_2, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_server_deserialize__invalid_method, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_server_deserialize__invalid_operand, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_server_deserialize__invalid_operand_2, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_server_deserialize__too_many_fields, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_server_deserialize__single_request, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_server_deserialize__multipart_request, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_server_deserialize__multipart_request_2, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_client_deserialize__invalid_req_id, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_client_deserialize__invalid_status, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_client_deserialize__invalid_status_2, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_client_deserialize__invalid_result, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_client_deserialize__single_response, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_client_deserialize__multipart_request_2, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_server_serialize_response, setup, teardown),
    cmocka_unit_test_setup_teardown(calc_client_serialize_request, setup, teardown)
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
