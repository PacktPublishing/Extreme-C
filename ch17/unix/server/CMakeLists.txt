cmake_minimum_required(VERSION 3.8)

add_executable(calc_unix_server
  calc_server.c
  main.c
)

target_link_libraries(calc_unix_server
  calcser
  calcsvc
)
