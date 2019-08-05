// File name: ExtremeC_exampels_chapter1_20.c
// Description: Example 1.20

#include <stdio.h>

typedef int bool_t;
typedef bool_t (*less_than_func_t)(int, int);

bool_t less_than(int a, int b) {
  return a < b ? 1 : 0;
}

bool_t less_than_modular(int a, int b) {
  return (a % 5) < (b % 5) ? 1 : 0;
}

int main(int argc, char** argv) {
  less_than_func_t func_ptr = NULL;
  
  func_ptr = &less_than;
  bool_t result = func_ptr(3, 7);
  printf("%d\n", result);
  
  func_ptr = &less_than_modular;
  result = func_ptr(3, 7);
  printf("%d\n", result);
  
  return 0;
}
