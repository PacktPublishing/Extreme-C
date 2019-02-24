cmake_minimum_required(VERSION 3.8)

add_executable(ex14_1.out
  ExtremeC_examples_chapter14_1.c
)

add_executable(ex14_2.out
  ExtremeC_examples_chapter14_2.c
)

add_executable(ex14_3.out
  ExtremeC_examples_chapter14_3.c
)

add_executable(ex14_4.out
  ExtremeC_examples_chapter14_4.c
)

add_executable(ex14_5.out
  ExtremeC_examples_chapter14_5.c
)

add_executable(ex14_6.out
  ExtremeC_examples_chapter14_6.c
)

add_executable(ex14_14_7.out
  ExtremeC_examples_chapter14_7.c
)

if (UNIX AND NOT APPLE)
target_link_libraries(ex14_4.out
  rt
)

target_link_libraries(ex14_5.out
  rt
)

target_link_libraries(ex14_6.out
  rt
)
endif()
