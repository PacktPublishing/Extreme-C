cmake_minimum_required(VERSION 3.8)

add_executable(ex15_3_mutex.out
  ExtremeC_examples_chapter15_3_mutex.c
)

target_link_libraries(ex15_3_mutex.out
  pthread
)

add_executable(ex15_3_sem.out
  ExtremeC_examples_chapter15_3_sem.c
)

target_link_libraries(ex15_3_sem.out
  pthread
)
add_executable(ex16_1_cv.out
  ExtremeC_examples_chapter16_1_cv.c
)

target_link_libraries(ex16_1_cv.out
  pthread
)

if (NOT APPLE)

add_executable(ex16_1_barrier.out
  ExtremeC_examples_chapter16_1_barrier.c
)

target_link_libraries(ex16_1_barrier.out
  pthread
)

endif()

add_executable(ex16_2.out
  ExtremeC_examples_chapter16_2.c
)

target_link_libraries(ex16_2.out
  pthread
)

add_executable(ex16_3.out
  ExtremeC_examples_chapter16_3.c
)

target_link_libraries(ex16_3.out
  pthread
)

add_executable(ex16_4.out
  ExtremeC_examples_chapter16_4.c
)

target_link_libraries(ex16_4.out
  pthread
)

add_executable(ex16_5_raw.out
  ExtremeC_examples_chapter16_5_raw.c
)

target_link_libraries(ex16_5_raw.out
  pthread
)

if (NOT APPLE)

add_executable(ex16_5.out
  ExtremeC_examples_chapter16_5.c
)

target_link_libraries(ex16_5.out
  pthread
)

endif()

add_executable(ex16_6.out
  ExtremeC_examples_chapter16_6.c
)

target_link_libraries(ex16_6.out
  pthread
)
