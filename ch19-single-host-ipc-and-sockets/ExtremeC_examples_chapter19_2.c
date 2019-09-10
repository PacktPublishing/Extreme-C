// File name: ExtremeC_examples_chapter19_2.c
// Description: POSIX pipe example

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char** argv) {
  int fds[2];
  pipe(fds);

  int childpid = fork();
  if (childpid == -1) {
    fprintf(stderr, "fork error!\n");
    exit(1);
  }
  if (childpid == 0) {
    // Child closes the read file descriptor
    close(fds[0]);
    char str[] = "Hello Daddy!";
    // Child writes to the write file descriptor
    fprintf(stdout, "CHILD: Waiting for 2 seconds ...\n");
    sleep(2);
    fprintf(stdout, "CHILD: Writing to daddy ...\n");
    write(fds[1], str, strlen(str) + 1);
  } else {
    // Parent closes the write file descriptor
    close(fds[1]);
    char buff[32];
    // Parent reads from the read file descriptor
    fprintf(stdout, "PARENT: Reading from child ...\n");
    int num_of_read_bytes = read(fds[0], buff, 32);
    fprintf(stdout, "PARENT: Received from child: %s\n", buff);
  }
  return 0;
}
