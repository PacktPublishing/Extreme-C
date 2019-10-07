cmake_minimum_required(VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ex9_1.out
  ExtremeC_examples_chapter9_1.c
)

add_library(ex9_2 STATIC
  ExtremeC_examples_chapter9_2.c
  ExtremeC_examples_chapter9_2.cpp
)

add_library(ex9_3 STATIC
  ExtremeC_examples_chapter9_3.cpp
)
