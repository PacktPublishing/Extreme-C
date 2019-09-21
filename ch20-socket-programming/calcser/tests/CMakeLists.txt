cmake_minimum_required(VERSION 3.8)

add_executable(calc_proto_tests
  calc_proto_tests.c
)

target_link_libraries(calc_proto_tests
  cmocka
  calcser
)
