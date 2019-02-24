cmake_minimum_required(VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ex5_1.out
  ExtremeC_examples_chapter5_1.c
)

add_executable(ex5_2.out
  ExtremeC_examples_chapter5_2_person.c
  ExtremeC_examples_chapter5_2_student.c
  ExtremeC_examples_chapter5_2_main.c
)

add_executable(ex5_3.out
  ExtremeC_examples_chapter5_3_person.c
  ExtremeC_examples_chapter5_3_student.c
  ExtremeC_examples_chapter5_3_main.c
)

add_executable(ex5_4.out
  ExtremeC_examples_chapter5_4_animal.c
  ExtremeC_examples_chapter5_4_cat.c
  ExtremeC_examples_chapter5_4_duck.c
  ExtremeC_examples_chapter5_4_main.c
)

add_executable(ex5_5.out
  ExtremeC_examples_chapter5_5.c
)

add_library(ex5_6 STATIC
  ExtremeC_examples_chapter5_6.c
  ExtremeC_examples_chapter5_6.cpp
)

add_library(ex5_7 STATIC
  ExtremeC_examples_chapter5_7.cpp
)

add_executable(ex5_8.out
  ExtremeC_examples_chapter5_8_list.c
  ExtremeC_examples_chapter5_8_main.c
)
