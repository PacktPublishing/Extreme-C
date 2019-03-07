cmake_minimum_required(VERSION 3.8)

add_executable(ex10_3_mutex.out
  ExtremeC_examples_chapter10_3_mutex.c
)

target_link_libraries(ex10_3_mutex.out
  pthread
)

add_executable(ex10_3_sem.out
  ExtremeC_examples_chapter10_3_sem.c
)

target_link_libraries(ex10_3_sem.out
  pthread
)

add_executable(ex11_1_cv.out
  ExtremeC_examples_chapter11_1_cv.c
)

target_link_libraries(ex11_1_cv.out
  pthread
)

if (NOT APPLE)

add_executable(ex11_1_barrier.out
  ExtremeC_examples_chapter11_1_barrier.c
)

target_link_libraries(ex11_1_barrier.out
  pthread
)

endif()

add_executable(ex11_2.out
  ExtremeC_examples_chapter11_2.c
)

target_link_libraries(ex11_2.out
  pthread
)

add_executable(ex11_3.out
  ExtremeC_examples_chapter11_3.c
)

target_link_libraries(ex11_3.out
  pthread
)

add_executable(ex11_4.out
  ExtremeC_examples_chapter11_4.c
)

target_link_libraries(ex11_4.out
  pthread
)

add_executable(ex11_5_raw.out
  ExtremeC_examples_chapter11_5_raw.c
)

target_link_libraries(ex11_5_raw.out
  pthread
)

if (NOT APPLE)

add_executable(ex11_5.out
  ExtremeC_examples_chapter11_5.c
)

target_link_libraries(ex11_5.out
  pthread
)

endif()

add_executable(ex11_6.out
  ExtremeC_examples_chapter11_6.c
)

target_link_libraries(ex11_6.out
  pthread
)
