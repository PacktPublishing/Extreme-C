// File name: ExtremeC_examples_chapter3_4.c
// Description: Load the shared object file using dlopen

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "ExtremeC_examples_chapter3_2_geometry.h"

polar_pos_2d_t (*func_ptr)(cartesian_pos_2d_t*);

int main(int argc, char** argv) {

  void* handle = dlopen ("/opt/geometry/libgeometry.so", RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }

  func_ptr = dlsym(handle, "convert_to_2d_polar_pos");
  if (!func_ptr)  {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }

  cartesian_pos_2d_t cartesian_pos;
  cartesian_pos.x = 100;
  cartesian_pos.y = 200;
  polar_pos_2d_t polar_pos = func_ptr(&cartesian_pos);
  printf("Polar Position: Length: %f, Theta: %f (deg)\n",
    polar_pos.length, polar_pos.theta);
  return 0;
}
