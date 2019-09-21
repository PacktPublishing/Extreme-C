cmake_minimum_required(VERSION 3.8)

add_library(clicore STATIC
  common_client_core.c
  stream_client_core.c
  datagram_client_core.c
)

target_link_libraries(clicore
  calcser
  calcsvc
)
