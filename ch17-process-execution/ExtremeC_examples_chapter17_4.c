// File name: ExtremeC_examples_chapter17_4.c
// Description: An example on how to create a shared
//              memory object.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

#define SH_SIZE 16

int main(int argc, char** argv) {
  int shm_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
  if (shm_fd < 0) {
    fprintf(stderr, "ERROR: Failed to create shared memory: %s\n",
        strerror(errno));
    return 1;
  }
  fprintf(stdout, "Shared memory is created with fd: %d\n",
          shm_fd);
  if (ftruncate(shm_fd, SH_SIZE * sizeof(char)) < 0) {
    fprintf(stderr, "ERROR: Truncation failed: %s\n",
            strerror(errno));
    return 1;
  }
  fprintf(stdout, "The memory region is truncated.\n");
  void* map = mmap(0, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (map == MAP_FAILED) {
    fprintf(stderr, "ERROR: Mapping failed: %s\n",
            strerror(errno));
    return 1;
  }
  char* ptr = (char*)map;
  ptr[0] = 'A';
  ptr[1] = 'B';
  ptr[2] = 'C';
  ptr[3] = '\n';
  ptr[4] = '\0';
  while(1);
  fprintf(stdout, "Data is written to the shared memory.\n");
  if (munmap(ptr, SH_SIZE) < 0) {
    fprintf(stderr, "ERROR: Unmapping failed: %s\n",
            strerror(errno));
    return 1;
  }
  if (close(shm_fd) < 0) {
    fprintf(stderr, "ERROR: Closing shared memory failed: %s\n",
        strerror(errno));
    return 1;
  }
  return 0;
}
