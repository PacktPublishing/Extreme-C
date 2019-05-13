cmake_minimum_required(VERSION 3.8)

add_executable(udp_calc_client
  main.c
)

target_link_libraries(udp_calc_client
  clicore
  pthread
)
