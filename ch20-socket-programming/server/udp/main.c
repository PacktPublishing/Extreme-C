#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <datagram_server_core.h>

struct sockaddr* sockaddr_new() {
  return malloc(sizeof(struct sockaddr_in));
}

socklen_t sockaddr_sizeof() {
  return sizeof(struct sockaddr_in);
}

int main(int argc, char** argv) {

  // ----------- 1. Create socket object ------------------
  int server_sd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sd == -1) {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 2. Bind the socket file ------------------

  // Prepare the address
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(9999);

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
