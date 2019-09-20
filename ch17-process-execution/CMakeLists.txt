cmake_minimum_required(VERSION 3.8)

add_executable(ex17_1.out
  ExtremeC_examples_chapter17_1.c
)

add_executable(ex17_2.out
  ExtremeC_examples_chapter17_2.c
)

add_executable(ex17_3.out
  ExtremeC_examples_chapter17_3.c
)

add_executable(ex17_4.out
  ExtremeC_examples_chapter17_4.c
)

add_executable(ex17_5.out
  ExtremeC_examples_chapter17_5.c
)

add_executable(ex17_6.out
  ExtremeC_examples_chapter17_6.c
)

add_executable(ex17_7.out
  ExtremeC_examples_chapter17_7.c
)

if (UNIX AND NOT APPLE)
target_link_libraries(ex17_4.out
  rt
)

target_link_libraries(ex17_5.out
  rt
)

target_link_libraries(ex17_6.out
  rt
)
endif()
