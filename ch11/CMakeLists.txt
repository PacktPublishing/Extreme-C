cmake_minimum_required(VERSION 3.8)

add_executable(ExtremeC_examples_chapter11_1
  ExtremeC_examples_chapter11_1.c
)

add_executable(ExtremeC_examples_chapter11_2
  ExtremeC_examples_chapter11_2.c
)

add_executable(ExtremeC_examples_chapter11_3
  ExtremeC_examples_chapter11_3.c
)

add_executable(ExtremeC_examples_chapter11_4
  ExtremeC_examples_chapter11_4.c
)

add_executable(ExtremeC_examples_chapter11_5
  ExtremeC_examples_chapter11_5.c
)

add_executable(ExtremeC_examples_chapter11_6
  ExtremeC_examples_chapter11_6.c
)

add_executable(ExtremeC_examples_chapter11_7
  ExtremeC_examples_chapter11_7.c
)

add_executable(ExtremeC_examples_chapter11_8
  ExtremeC_examples_chapter11_8.c
)

add_executable(ExtremeC_examples_chapter11_9
  ExtremeC_examples_chapter11_9.c
)

add_executable(ExtremeC_examples_chapter11_10
  ExtremeC_examples_chapter11_10.c
)

add_executable(ExtremeC_examples_chapter11_11
  ex11_11/ExtremeC_examples_chapter11_11_shared_mem.c
  ex11_11/ExtremeC_examples_chapter11_11_shared_int32.c
  ex11_11/ExtremeC_examples_chapter11_11_shared_mutex.c
  ex11_11/ExtremeC_examples_chapter11_11_shared_cond.c
  ex11_11/ExtremeC_examples_chapter11_11_main.c
)

if (UNIX AND NOT APPLE)
target_link_libraries(ExtremeC_examples_chapter11_4
  rt
)

target_link_libraries(ExtremeC_examples_chapter11_5
  rt
)

target_link_libraries(ExtremeC_examples_chapter11_6
  rt
)

target_link_libraries(ExtremeC_examples_chapter11_8
  rt
  pthread
)

target_link_libraries(ExtremeC_examples_chapter11_9
  rt
  pthread
)

target_link_libraries(ExtremeC_examples_chapter11_10
  rt
  pthread
)

target_link_libraries(ExtremeC_examples_chapter11_11
  rt
  pthread
)
endif()
