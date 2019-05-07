cmake_minimum_required(VERSION 3.8)

add_executable(calc_unix_client
  calc_client.c
  main.c
)

target_link_libraries(calc_unix_client
  calcser
)
