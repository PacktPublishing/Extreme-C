#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void client_loop(int conn_fd) {
  char buf[128];
  while (1) {
    printf("? ");
    scanf("%s", buf);
    int sign_found = 0;
    if (strstr(buf, "++")) {
    }
  }
  printf("Bye.\n");
}
