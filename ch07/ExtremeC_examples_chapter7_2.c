// File name: ExtremeC_examples_chapter7_2.c
// Description: Invoke the hello world system call

// We need to have this to be able to use non-POSIX stuff
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>

// Thse is not part of POSIX!
#include <sys/syscall.h>

int main(int argc, char** argv) {
  char str[20] = "Kam";
  char message[64] = "";

  // Call the hello world system call
  int ret_val = syscall(999, str, 4, message, 64);
  if (ret_val < 0) {
    printf("[ERR] Ret val: %d\n", ret_val);
    return 1;
  }
  printf("Message: %s\n", message);
  return 0;
}
