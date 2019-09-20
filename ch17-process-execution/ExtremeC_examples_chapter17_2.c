// File name: ExtremeC_examples_chapter17_2.c
// Description: This example tries to show the non-determinstic
//              nature of two concurrent processes.

#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
  pid_t ret = fork();
  if (ret) {
    for (size_t i = 0; i < 5; i++) {
      printf("AAA\n");
      usleep(1);
    }
  } else {
    for (size_t i = 0; i < 5; i++) {
      printf("BBBBBB\n");
      usleep(1);
    }
  }
  return 0;
}
