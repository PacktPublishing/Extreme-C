cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_FLAGS "-g")
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(cstack SHARED
  cstack.c
)

add_executable(cstack_tests.out
  cstack_tests.c
)

target_link_libraries(cstack_tests.out
  cstack
)

add_subdirectory(java/native)
