#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <datagram_client_core.h>

int main(int argc, char** argv) {
  char server_sock_file[] = "/tmp/calc_svc.sock";
  char client_sock_file[] = "/tmp/calc_cli.sock";

  // ----------- 1. Create socket object ------------------

  int conn_sd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (conn_sd == -1) {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 2. Bind the client socket file ------------

  // Delete the previously created socket file if it exists.
  unlink(client_sock_file);

  // Prepare the client address
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, client_sock_file,
          sizeof(addr.sun_path) - 1);

  int result = bind(conn_sd,
          (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) {
    close(conn_sd);
    fprintf(stderr, "Could not bind the client address: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 3. Connect to server --------------------

  // Prepare the server address
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, server_sock_file,
          sizeof(addr.sun_path) - 1);

  result = connect(conn_sd,
          (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) {
    close(conn_sd);
    fprintf(stderr, "Could no connect: %s\n", strerror(errno));
    exit(1);
  }

  datagram_client_loop(conn_sd);

  return 0;
}
