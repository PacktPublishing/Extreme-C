cmake_minimum_required(VERSION 3.8)

add_subdirectory(tests)

add_library(calcsvc SHARED
  calc_service.c
)
