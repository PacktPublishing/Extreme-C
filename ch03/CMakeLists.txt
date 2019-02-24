set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ex3_1.out
  ExtremeC_examples_chapter3_1.c
  ExtremeC_examples_chapter3_1_main.c
)

add_executable(ex3_2.out
  ExtremeC_examples_chapter3_2.c
)

add_library(ex3_3 STATIC
  ExtremeC_examples_chapter3_3.c
)

add_executable(ex3_4.out
  ExtremeC_examples_chapter3_4_add.c
  ExtremeC_examples_chapter3_4_multiply.c
  ExtremeC_examples_chapter3_4_main.c
)

add_executable(ex3_5.out
  ExtremeC_examples_chapter3_5_add.c
  ExtremeC_examples_chapter3_5_main.c
)

add_library(ex3_6 STATIC
  ExtremeC_examples_chapter3_6_add_1.c
  ExtremeC_examples_chapter3_6_add_2.c
)

add_executable(ex3_7.out
  ExtremeC_examples_chapter3_7_funcs.c
  ExtremeC_examples_chapter3_7.c
)

add_library(geometry STATIC SHARED
  ExtremeC_examples_chapter3_8_2d.c
  ExtremeC_examples_chapter3_8_3d.c
  ExtremeC_examples_chapter3_8_trigon.c
)

add_executable(ex3_9.out
  ExtremeC_examples_chapter3_9.c
)

target_link_libraries(ex3_9.out
  geometry
)

add_executable(ex3_10.out
  ExtremeC_examples_chapter3_10.c
)
