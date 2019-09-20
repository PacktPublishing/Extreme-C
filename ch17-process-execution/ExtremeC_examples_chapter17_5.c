// File name: ExtremeC_examples_chapter17_5.c
// Description: An example on how to read a shared memory object.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

#define SH_SIZE 16

int main(int argc, char** argv) {
  int shm_fd = shm_open("/shm0", O_RDONLY, 0600);
  if (shm_fd < 0) {
    fprintf(stderr, "ERROR: Failed to open shared memory: %s\n",
        strerror(errno));
    return 1;
  }
  fprintf(stdout, "Shared memory is opened with fd: %d\n", shm_fd);
  void* map = mmap(0, SH_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
  if (map == MAP_FAILED) {
    fprintf(stderr, "ERROR: Mapping failed: %s\n",
            strerror(errno));
    return 1;
  }
  char* ptr = (char*)map;
  fprintf(stdout, "The contents of shared memory object: %s\n",
          ptr);
  if (munmap(ptr, SH_SIZE) < 0) {
    fprintf(stderr, "ERROR: Unmapping failed: %s\n",
            strerror(errno));
    return 1;
  }
  if (close(shm_fd) < 0) {
    fprintf(stderr, "ERROR: Closing shared memory fd filed: %s\n",
        strerror(errno));
    return 1;
  }
  if (shm_unlink("/shm0") < 0) {
    fprintf(stderr, "ERROR: Unlinking shared memory failed: %s\n",
        strerror(errno));
    return 1;
  }
  return 0;
}
