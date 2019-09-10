cmake_minimum_required(VERSION 3.8)

add_executable(ex19_1.out
  ExtremeC_examples_chapter19_1.c
)

add_executable(ex19_2.out
  ExtremeC_examples_chapter19_2.c
)

if (NOT APPLE)
add_executable(ex19_3.out
  ExtremeC_examples_chapter19_3.c
)

target_link_libraries(ex19_3.out
  rt
)
endif()
