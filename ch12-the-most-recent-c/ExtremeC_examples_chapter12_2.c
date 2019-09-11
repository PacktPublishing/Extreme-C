/* File name: ExtremeC_examples_chapter12_2.c
 * Description: Type generic macros
 */

#include <stdio.h>

#define abs(x) _Generic((x), \
                        int: absi, \
                        double: absd)(x)
int absi(int a) {
  return a > 0 ? a : -a;
}

double absd(double a) {
  return a > 0 ? a : -a;
}

int main(int argc, char** argv) {
  printf("abs(-2): %d\n", abs(-2));
  printf("abs(2.5): %f\n", abs(2.5));;
  return 0;
}
