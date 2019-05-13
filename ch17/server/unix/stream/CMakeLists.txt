cmake_minimum_required(VERSION 3.8)

add_executable(unix_stream_calc_server
  main.c
)

target_link_libraries(unix_stream_calc_server
  srvcore
)
