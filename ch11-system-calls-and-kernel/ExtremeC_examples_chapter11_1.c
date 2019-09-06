// File name: ExtremeC_examples_chapter11_1.c
// Description: Hello world with direct system call

// We need to have this to be able to use non-POSIX stuff
#define _GNU_SOURCE

#include <unistd.h>

// This is not part of POSIX!
#include <sys/syscall.h>

int main(int argc, char** argv) {
  char message[20] = "Hello World!\n";
  // Invokes the 'write' system call that writes
  // some bytes into the standard output.
  syscall(__NR_write, 1, message, 13);
  return 0;
}
