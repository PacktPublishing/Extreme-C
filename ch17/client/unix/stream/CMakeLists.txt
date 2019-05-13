cmake_minimum_required(VERSION 3.8)

add_executable(unix_stream_calc_client
  main.c
)

target_link_libraries(unix_stream_calc_client
  clicore
  pthread
)
