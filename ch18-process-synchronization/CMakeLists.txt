cmake_minimum_required(VERSION 3.8)

SET(CMAKE_C_FLAGS  "-g")

add_executable(ex18_1.out
  ExtremeC_examples_chapter18_1.c
)

add_executable(ex18_2.out
  ExtremeC_examples_chapter18_2.c
)

add_executable(ex18_3.out
  ExtremeC_examples_chapter18_3.c
)

add_executable(ex18_4.out
  ex18_4/ExtremeC_examples_chapter18_4_shared_mem.c
  ex18_4/ExtremeC_examples_chapter18_4_shared_int32.c
  ex18_4/ExtremeC_examples_chapter18_4_shared_mutex.c
  ex18_4/ExtremeC_examples_chapter18_4_shared_cond.c
  ex18_4/ExtremeC_examples_chapter18_4_main.c
)

if (UNIX AND NOT APPLE)
target_link_libraries(ex18_1.out
  rt
  pthread
)

target_link_libraries(ex18_2.out
  rt
  pthread
)

target_link_libraries(ex18_3.out
  rt
  pthread
)

target_link_libraries(ex18_4.out
  rt
  pthread
)

endif()
