/* File name: ExtremeC_examples_chapter12_4.c
 * Description: Anonymous structures and unions
 */

#include <stdio.h>

typedef struct {
  union {
    struct {
      int x;
      int y;
    };
    int data[2];
  };
} point_t;

int main(int argc, char** argv) {
  point_t p;
  p.x = 10;
  p.data[1] = -5;
  printf("Point (%d, %d) using anonymous structure.\n", p.x, p.y);
  printf("Point (%d, %d) using anonymous byte array.\n",
      p.data[0], p.data[1]);
  return 0;
}
