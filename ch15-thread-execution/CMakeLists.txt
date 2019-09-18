cmake_minimum_required(VERSION 3.8)

add_executable(ex15_1.out
  ExtremeC_examples_chapter15_1.c
)

target_link_libraries(ex15_1.out
  pthread
)

add_executable(ex15_1_2.out
  ExtremeC_examples_chapter15_1_2.c
)

target_link_libraries(ex15_1_2.out
  pthread
)

add_executable(ex15_2.out
  ExtremeC_examples_chapter15_2.c
)

target_link_libraries(ex15_2.out
  pthread
)

add_executable(ex15_2_1.out
  ExtremeC_examples_chapter15_2_1.c
)

target_link_libraries(ex15_2_1.out
  pthread
)

add_executable(ex15_3.out
  ExtremeC_examples_chapter15_3.c
)

target_link_libraries(ex15_3.out
  pthread
)
