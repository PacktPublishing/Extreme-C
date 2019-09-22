#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <datagram_server_core.h>

struct sockaddr* sockaddr_new() {
  return malloc(sizeof(struct sockaddr_un));
}

socklen_t sockaddr_sizeof() {
  return sizeof(struct sockaddr_un);
}

int main(int argc, char** argv) {
  char sock_file[] = "/tmp/calc_svc.sock";

  // ----------- 1. Create socket object ------------------
  int server_sd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (server_sd == -1) {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
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

  int result = bind(server_sd,
          (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) {
    close(server_sd);
    fprintf(stderr, "Could not bind the address: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 3. Start serving requests ---------
  serve_forever(server_sd);

  return 0;
}
