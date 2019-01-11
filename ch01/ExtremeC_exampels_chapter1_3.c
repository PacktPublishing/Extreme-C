// File name: ExtremeC_exampels_chapter1_3.c
// Description: Example 1.3

#include <stdio.h>

#define PRINT(a) printf("%d\n", a);
#define LOOP(v, s, e) for (int v = s; v <= e; v++) {
#define ENDLOOP }

int main(int argc, char** argv) {
  LOOP(counter, 1, 10)
    PRINT(counter)
  ENDLOOP
  return 0;
}
