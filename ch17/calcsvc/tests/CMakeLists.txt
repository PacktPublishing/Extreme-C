cmake_minimum_required(VERSION 3.8)

add_executable(calc_service_tests
  calc_service_tests.c
)

target_link_libraries(calc_service_tests
  cmocka
  calcsvc
)
