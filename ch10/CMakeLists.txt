cmake_minimum_required(VERSION 3.8)

add_executable(ex10_1.out
  ExtremeC_examples_chapter10_1.c
)

target_link_libraries(ex10_1.out
  pthread
)

add_executable(ex10_1_2.out
  ExtremeC_examples_chapter10_1_2.c
)

target_link_libraries(ex10_1_2.out
  pthread
)

add_executable(ex10_2.out
  ExtremeC_examples_chapter10_2.c
)

target_link_libraries(ex10_2.out
  pthread
)

add_executable(ex10_2_1.out
  ExtremeC_examples_chapter10_2_1.c
)

target_link_libraries(ex10_2_1.out
  pthread
)

add_executable(ex10_3.out
  ExtremeC_examples_chapter10_3.c
)

target_link_libraries(ex10_3.out
  pthread
)
