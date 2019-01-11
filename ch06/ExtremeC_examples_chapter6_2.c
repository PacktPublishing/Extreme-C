// File name: ExtremeC_examples_chapter6_2.c
// Description: Hello world with direct system call

// We need to have this to be able to use non-POSIX stuff
#define _GNU_SOURCE

#include <unistd.h>

// This is not part of POSIX!
#include <sys/syscall.h>

int main(int argc, char** argv) {
  char message[20] = "Hello World!\n";
  // Calls the write system call which easily some bytes into a file.
  syscall(__NR_write, 1, message, 13);
  return 0;
}
