cmake_minimum_required(VERSION 3.8)

add_executable(ex16_1.out
  ExtremeC_examples_chapter16_1.c
)

add_executable(ex16_2.out
  ExtremeC_examples_chapter16_2.c
)

if (NOT APPLE)
add_executable(ex16_3.out
  ExtremeC_examples_chapter16_3.c
)

target_link_libraries(ex16_3.out
  rt
)
endif()
