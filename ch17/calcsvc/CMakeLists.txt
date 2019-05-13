cmake_minimum_required(VERSION 3.8)

add_subdirectory(tests)

add_library(calcsvc STATIC
  calc_service.c
)
