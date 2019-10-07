cmake_minimum_required(VERSION 3.8)

add_subdirectory(googletest)

include_directories(/usr/local/include googletest/googletest/include googletest/googlemock/include)
link_directories(/usr/local/lib)

set(CMAKE_C_FLAGS "-g")
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

add_executable(ex22_1.out
  ExtremeC_examples_chapter22_1.c
  ExtremeC_examples_chapter22_1_main.c
)

add_executable(ex22_1_tests.out
  ExtremeC_examples_chapter22_1.c
  ExtremeC_examples_chapter22_1__next_even_number__tests.c
  ExtremeC_examples_chapter22_1__calc_factorial__tests.c
  ExtremeC_examples_chapter22_1_tests.c
)

add_executable(ex22_1_component_tests.out
  ExtremeC_examples_chapter22_1.c
  ExtremeC_examples_chapter22_1_component_tests.c
)

if (UNIX AND NOT APPLE)
add_executable(ex22_1_cmocka_tests.out
  ExtremeC_examples_chapter22_1.c
  ExtremeC_examples_chapter22_1_cmocka_tests.c
)
endif()

add_executable(ex22_1_gtests.out
  ExtremeC_examples_chapter22_1.c
  ExtremeC_examples_chapter22_1_gtests.cpp
)

if (UNIX AND NOT APPLE)
target_link_libraries(ex22_1_cmocka_tests.out
  cmocka
)
endif()

target_link_libraries(ex22_1_gtests.out
  gtest
  pthread
)

add_executable(ex22_2_cmocka_tests_with_stub.out
  ExtremeC_examples_chapter22_2.c
  ExtremeC_examples_chapter22_2_cmocka_tests_with_stub.c
)

add_executable(ex22_2_cmocka_tests_with_mock.out
  ExtremeC_examples_chapter22_2.c
  ExtremeC_examples_chapter22_2_cmocka_tests_with_mock.c
)

target_link_libraries(ex22_2_cmocka_tests_with_stub.out
  cmocka
)

target_link_libraries(ex22_2_cmocka_tests_with_mock.out
  cmocka
)

if (UNIX AND NOT APPLE)
set_target_properties(ex22_2_cmocka_tests_with_stub.out
        PROPERTIES
        LINK_FLAGS  "-Wl,--wrap=rand"
)

set_target_properties(ex22_2_cmocka_tests_with_mock.out
        PROPERTIES
        LINK_FLAGS  "-Wl,--wrap=rand"
)
endif()
