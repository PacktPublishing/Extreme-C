cmake_minimum_required(VERSION 3.8)

add_executable(tcp_calc_server
  main.c
)

target_link_libraries(tcp_calc_server
  srvcore
)
