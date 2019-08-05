// File name: ExtremeC_exampels_chapter1_21.c
// Description: Example 1.21

#include <stdio.h>

struct sample_t {
  char first;
  char second;
  char third;
  short fourth;
};

void print_size(struct sample_t* var) {
  printf("Size: %lu bytes\n", sizeof(*var));
}

void print_bytes(struct sample_t* var) {
  unsigned char* ptr = (unsigned char*)var;
  for (int i = 0; i < sizeof(*var); i++, ptr++) {
    printf("%d ", (unsigned int)*ptr);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  struct sample_t var;
  var.first = 'A';
  var.second = 'B';
  var.third = 'C';
  var.fourth = 765;
  print_size(&var);
  print_bytes(&var);
  return 0;
}
