// File name: ExtremeC_examples_chapter5_4.c
// Description: Example 5.4

#include <stdlib.h> // For heap memory functions

int main(int argc, char** argv) {
  char* ptr = (char*)malloc(16 * sizeof(char));
  // free(ptr);
  return 0;
}
