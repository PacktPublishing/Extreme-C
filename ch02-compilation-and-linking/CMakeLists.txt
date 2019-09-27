set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ex2_1.out
  ExtremeC_examples_chapter2_1.c
  ExtremeC_examples_chapter2_1_main.c
)

add_executable(ex2_2.out
  ExtremeC_examples_chapter2_2.c
)

add_library(ex2_3 STATIC
  ExtremeC_examples_chapter2_3.c
)

add_executable(ex2_4.out
  ExtremeC_examples_chapter2_4_add.c
  ExtremeC_examples_chapter2_4_multiply.c
  ExtremeC_examples_chapter2_4_main.c
)

add_executable(ex2_5.out
  ExtremeC_examples_chapter2_5_add.c
  ExtremeC_examples_chapter2_5_main.c
)

add_library(ex2_6 STATIC
  ExtremeC_examples_chapter2_6_add_1.c
  ExtremeC_examples_chapter2_6_add_2.c
)
