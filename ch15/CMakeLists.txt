cmake_minimum_required(VERSION 3.8)

add_executable(ex15_1.out
  ExtremeC_examples_chapter15_1.c
)

add_executable(ex15_2.out
  ExtremeC_examples_chapter15_2.c
)

add_executable(ex15_3.out
  ExtremeC_examples_chapter15_3.c
)

add_executable(ex15_4.out
  ex15_4/ExtremeC_examples_chapter15_4_shared_mem.c
  ex15_4/ExtremeC_examples_chapter15_4_shared_int32.c
  ex15_4/ExtremeC_examples_chapter15_4_shared_mutex.c
  ex15_4/ExtremeC_examples_chapter15_4_shared_cond.c
  ex15_4/ExtremeC_examples_chapter15_4_main.c
)

if (UNIX AND NOT APPLE)
target_link_libraries(ex15_1.out
  rt
  pthread
)

target_link_libraries(ex15_2.out
  rt
  pthread
)

target_link_libraries(ex15_3.out
  rt
  pthread
)

target_link_libraries(ex15_4.out
  rt
  pthread
)
endif()
