#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <sys/un.h>

void accept_forever(int server_fd);

int main(int argc, char** argv) {
  char sock_file[] = "/tmp/calc_svc.sock";

  // ----------- 1. Create socket object ------------------
  int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (server_fd == -1) {
    fprintf(stderr, "Could not create socket: %s\n", strerror(errno));
    exit(1);
  }

  // ----------- 2. Bind the socket file ------------------

  // Delete the previously created socket file if it exists.
  unlink(sock_file);

  // Prepare the address
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, sock_file, sizeof(addr.sun_path) - 1);

  int result = bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) {
    close(server_fd);
    fprintf(stderr, "Could not bind the address: %s\n", strerror(errno));
    exit(1);
  }

  // ----------- 3. Prepare backlog ------------------
  result = listen(server_fd, 10);
  if (result == -1) {
    close(server_fd);
    fprintf(stderr, "Could not set the backlog: %s\n", strerror(errno));
    exit(1);
  }

  // ----------- 4. Start accepting clients ---------
  accept_forever(server_fd);

  return 0;
}
