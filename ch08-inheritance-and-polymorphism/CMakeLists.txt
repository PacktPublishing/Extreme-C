cmake_minimum_required(VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ex8_1.out
  ExtremeC_examples_chapter8_1.c
)

add_executable(ex8_2.out
  ExtremeC_examples_chapter8_2_person.c
  ExtremeC_examples_chapter8_2_student.c
  ExtremeC_examples_chapter8_2_main.c
)

add_executable(ex8_3.out
  ExtremeC_examples_chapter8_3_person.c
  ExtremeC_examples_chapter8_3_student.c
  ExtremeC_examples_chapter8_3_main.c
)

add_executable(ex8_4.out
  ExtremeC_examples_chapter8_4_animal.c
  ExtremeC_examples_chapter8_4_cat.c
  ExtremeC_examples_chapter8_4_duck.c
  ExtremeC_examples_chapter8_4_main.c
)
