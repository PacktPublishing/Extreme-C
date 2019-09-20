// File name: ExtremeC_examples_chapter17_7.c
// Description: Demonstrate a data race between two processes
//              while using file system for storing the shared
//              state.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SH_SIZE 4

// The shared file descriptor used to refer to the shared file
int shared_fd = -1;

// The pointer to the shared counter
int32_t* counter = NULL;

void init_shared_resource() {
  // Open the file
  shared_fd = open("data.bin", O_CREAT | O_RDWR, 0600);
  if (shared_fd < 0) {
    fprintf(stderr, "ERROR: Failed to create the file: %s\n",
        strerror(errno));
    exit(1);
  }
  fprintf(stdout, "File is created and opened with fd: %d\n", 
          shared_fd);
}

void shutdown_shared_resource() {
  if (remove("data.bin") < 0) {
    fprintf(stderr, "ERROR: Removing the file failed: %s\n",
        strerror(errno));
    exit(1);
  }
}

void inc_counter() {
  usleep(1);
  int32_t temp = *counter;
  usleep(1);
  temp++;
  usleep(1);
  *counter = temp;
  usleep(1);
}

int main(int argc, char** argv) {

  // Parent process needs to initialize the shared resource
  init_shared_resource();

  // Allocate and truncate the shared memory region
  if (ftruncate(shared_fd, SH_SIZE * sizeof(char)) < 0) {
    fprintf(stderr, "ERROR: Truncation failed: %s\n",
            strerror(errno));
    return 1;
  }
  fprintf(stdout, "The memory region is truncated.\n");

  void* map = mmap(0, SH_SIZE, PROT_WRITE, MAP_SHARED,
          shared_fd, 0);
  if (map == MAP_FAILED) {
    fprintf(stderr, "ERROR: Mapping failed: %s\n",
            strerror(errno));
    return 1;
  }
  counter = (int32_t*)map;
  *counter = 0;

  // Fork a new process
  pid_t pid = fork();
  if (pid) { // The parent process
    // Incrmenet the counter
    inc_counter();
    fprintf(stdout, "The parent process sees the counter as %d.\n",
        *counter);

    // Wait for the child process to exit
    int status = -1;
    wait(&status);
    fprintf(stdout, "The child process finished with status %d.\n",
        status);
  } else { // The child process
    // Incrmenet the counter
    inc_counter();
    fprintf(stdout, "The child process sees the counter as %d.\n",
        *counter);
  }

  // Both processes should unmap shared memory region and close
  // its file descriptor
  if (munmap(counter, SH_SIZE) < 0) {
    fprintf(stderr, "ERROR: Unmapping failed: %s\n",
            strerror(errno));
    return 1;
  }
  if (close(shared_fd) < 0) {
    fprintf(stderr, "ERROR: Closing fd filed: %s\n",
        strerror(errno));
    return 1;
  }

  // Only parent process needs to shutdown the shared resource
  if (pid) {
    shutdown_shared_resource();
  }

  return 0;
}
