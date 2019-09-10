// File name: ExtremeC_examples_chapter19_1.c
// Description: Signal handling example

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_user_signals(int signal) {
  switch (signal) {
    case SIGUSR1:
      printf("SIGUSR1 received!\n");
      break;
    case SIGUSR2:
      printf("SIGUSR2 received!\n");
      break;
    default:
      printf("Unsupported signal is received!\n");
  }
}

void handle_sigint(int signal) {
  printf("Interrupt signal is received!\n");
}

void handle_sigkill(int signal) {
  printf("Kill signal is received! Bye.\n");
  exit(0);
}

int main(int argc, char** argv) {
  signal(SIGUSR1, handle_user_signals);
  signal(SIGUSR2, handle_user_signals);
  signal(SIGINT, handle_sigint);
  signal(SIGKILL, handle_sigkill);
  while (1);
  return 0;
}
