cmake_minimum_required(VERSION 3.8)

include_directories($ENV{JAVA_HOME}/include)

if (APPLE)
  include_directories($ENV{JAVA_HOME}/include/darwin)
elseif (UNIX)
  include_directories($ENV{JAVA_HOME}/include/linux)
endif()

add_library(NativeStack SHARED
  NativeStack.cpp
)

target_link_libraries(NativeStack
  cstack
)

#if (APPLE)
#  set_property(TARGET NativeStack PROPERTY PREFIX "lib")
#  set_property(TARGET NativeStack PROPERTY OUTPUT_NAME "NativeStack.so")
#  set_property(TARGET NativeStack PROPERTY SUFFIX "")
#endif()
