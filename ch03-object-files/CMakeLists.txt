cmake_minimum_required(VERSION 3.6)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ex3_1.out
  ExtremeC_examples_chapter3_1_funcs.c
  ExtremeC_examples_chapter3_1.c
)

add_library(geometry STATIC SHARED
  ExtremeC_examples_chapter3_2_2d.c
  ExtremeC_examples_chapter3_2_3d.c
  ExtremeC_examples_chapter3_2_trigon.c
)

add_executable(ex3_3.out
  ExtremeC_examples_chapter3_3.c
)

target_link_libraries(ex3_3.out
  geometry
  m
)

add_executable(ex3_4.out
  ExtremeC_examples_chapter3_4.c
)

target_link_libraries(ex3_4.out
  dl
)
