cmake_minimum_required(VERSION 3.8)

include_directories(/usr/local/include)
include_directories(calcser)
include_directories(calcsvc)

link_directories(/usr/local/lib)

add_compile_options("-g")

add_subdirectory(calcser)
add_subdirectory(calcsvc)
add_subdirectory(unix)
