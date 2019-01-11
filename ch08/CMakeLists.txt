cmake_minimum_required(VERSION 3.8)

add_executable(ExtremeC_examples_chapter8_1
  ExtremeC_examples_chapter8_1.c
)

target_link_libraries(ExtremeC_examples_chapter8_1
  pthread
)

add_executable(ExtremeC_examples_chapter8_1_2
  ExtremeC_examples_chapter8_1_2.c
)

target_link_libraries(ExtremeC_examples_chapter8_1_2
  pthread
)

add_executable(ExtremeC_examples_chapter8_2
  ExtremeC_examples_chapter8_2.c
)

target_link_libraries(ExtremeC_examples_chapter8_2
  pthread
)

add_executable(ExtremeC_examples_chapter8_2_1
  ExtremeC_examples_chapter8_2_1.c
)

target_link_libraries(ExtremeC_examples_chapter8_2_1
  pthread
)

add_executable(ExtremeC_examples_chapter8_3
  ExtremeC_examples_chapter8_3.c
)

target_link_libraries(ExtremeC_examples_chapter8_3
  pthread
)

add_executable(ExtremeC_examples_chapter8_3_mutex
  ExtremeC_examples_chapter8_3_mutex.c
)

target_link_libraries(ExtremeC_examples_chapter8_3_mutex
  pthread
)

add_executable(ExtremeC_examples_chapter8_3_sem
  ExtremeC_examples_chapter8_3_sem.c
)

target_link_libraries(ExtremeC_examples_chapter8_3_sem
  pthread
)

add_executable(ExtremeC_examples_chapter8_4_cv
  ExtremeC_examples_chapter8_4_cv.c
)

target_link_libraries(ExtremeC_examples_chapter8_4_cv
  pthread
)

if (NOT APPLE)

add_executable(ExtremeC_examples_chapter8_4_barrier
  ExtremeC_examples_chapter8_4_barrier.c
)

target_link_libraries(ExtremeC_examples_chapter8_4_barrier
  pthread
)

endif()

add_executable(ExtremeC_examples_chapter8_5
  ExtremeC_examples_chapter8_5.c
)

target_link_libraries(ExtremeC_examples_chapter8_5
  pthread
)

add_executable(ExtremeC_examples_chapter8_6
  ExtremeC_examples_chapter8_6.c
)

target_link_libraries(ExtremeC_examples_chapter8_6
  pthread
)

add_executable(ExtremeC_examples_chapter8_7
  ExtremeC_examples_chapter8_7.c
)

target_link_libraries(ExtremeC_examples_chapter8_7
  pthread
)

add_executable(ExtremeC_examples_chapter8_8_raw
  ExtremeC_examples_chapter8_8_raw.c
)

target_link_libraries(ExtremeC_examples_chapter8_8_raw
  pthread
)

if (NOT APPLE)

add_executable(ExtremeC_examples_chapter8_8
  ExtremeC_examples_chapter8_8.c
)

target_link_libraries(ExtremeC_examples_chapter8_8
  pthread
)

endif()

add_executable(ExtremeC_examples_chapter8_9
  ExtremeC_examples_chapter8_9.c
)

target_link_libraries(ExtremeC_examples_chapter8_9
  pthread
)
