cmake_minimum_required(VERSION 3.8)

add_subdirectory(tests)

add_library(calcser SHARED
  calc_proto_ser.c
  calc_proto_req.c
)
