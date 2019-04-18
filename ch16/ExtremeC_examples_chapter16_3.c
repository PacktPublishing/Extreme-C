// File name: ExtremeC_examples_chapter16_3.c
// Description: Message queue example

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>

int main(int argc, char** argv) {
  // The message queue handler
  mqd_t mq;

  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 32;
  attr.mq_curmsgs = 0;


  int childpid = fork();
  if (childpid == -1) {
    fprintf(stderr, "fork error!\n");
    exit(1);
  }
  if (childpid == 0) {
    // Child waits while the parent is creating the queue
    sleep(1);
    mqd_t mq = mq_open("/mq0", O_WRONLY);
    char str[] = "Hello Daddy!";
    // Child writes to the write file descriptor
    fprintf(stdout, "CHILD: Waiting for 2 seconds ...\n");
    sleep(2);
    fprintf(stdout, "CHILD: Writing to daddy ...\n");
    mq_send(mq, str, strlen(str) + 1, 0);
    mq_close(mq);
  } else {
    mqd_t mq = mq_open("/mq0", O_RDONLY | O_CREAT, 0644, &attr);
    char buff[32];
    fprintf(stdout, "PARENT: Reading from child ...\n");
    int num_of_read_bytes = mq_receive(mq, buff, 32, NULL);
    fprintf(stdout, "PARENT: Received from child: %s\n", buff);
    mq_close(mq);
    mq_unlink("/mq0");
  }
  return 0;
}
