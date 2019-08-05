// File name: ExtremeC_exampels_chapter1_14.c
// Description: Example 1.14

#include <stdio.h>

void print_bytes(void* data, size_t length) {
  char delim = ' ';
  unsigned char* ptr = data;
  for (size_t i = 0; i < length; i++) {
    printf("%c 0x%x", delim, *ptr);
    delim = ',';
    ptr++;
  }
  printf("\n");
}

int main(int argc, char** argv) {
 int a = 9;
 double b = 18.9;

 print_bytes(&a, sizeof(int));
 print_bytes(&b, sizeof(double));

 return 0;
}
