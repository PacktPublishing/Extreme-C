cmake_minimum_required(VERSION 3.8)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(CMAKE_C_FLAGS "-g")
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

add_executable(ExtremeC_examples_chapter15_1
  ExtremeC_examples_chapter15_1.c
  ExtremeC_examples_chapter15_1_main.c
)

add_executable(ExtremeC_examples_chapter15_1_tests
  ExtremeC_examples_chapter15_1.c
  ExtremeC_examples_chapter15_1__next_even_number__tests.c
  ExtremeC_examples_chapter15_1__calc_factorial__tests.c
  ExtremeC_examples_chapter15_1_tests.c
)

add_executable(ExtremeC_examples_chapter15_1_component_tests
  ExtremeC_examples_chapter15_1.c
  ExtremeC_examples_chapter15_1_component_tests.c
)

if (UNIX AND NOT APPLE)
add_executable(ExtremeC_examples_chapter15_1_cmocka_tests
  ExtremeC_examples_chapter15_1.c
  ExtremeC_examples_chapter15_1_cmocka_tests.c
)
endif()

add_executable(ExtremeC_examples_chapter15_1_gtests
  ExtremeC_examples_chapter15_1.c
  ExtremeC_examples_chapter15_1_gtests.cpp
)

if (UNIX AND NOT APPLE)
target_link_libraries(ExtremeC_examples_chapter15_1_cmocka_tests
  cmocka
)
endif()

target_link_libraries(ExtremeC_examples_chapter15_1_gtests
  gtest
  pthread
)

add_executable(ExtremeC_examples_chapter15_2_cmocka_tests
  ExtremeC_examples_chapter15_2.c
  ExtremeC_examples_chapter15_2_cmocka_tests.c
)

target_link_libraries(ExtremeC_examples_chapter15_2_cmocka_tests
  cmocka
)

if (UNIX AND NOT APPLE)
set_target_properties(ExtremeC_examples_chapter15_2_cmocka_tests
        PROPERTIES
        LINK_FLAGS  "-Wl,--wrap=rand"
)
endif()
