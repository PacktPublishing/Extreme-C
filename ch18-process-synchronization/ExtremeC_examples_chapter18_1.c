// File name: ExtremeC_examples_chapter18_1.c
// Description: Demonstrates how to use a named semaphore to
//              protect a counter inside a shared memory region.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>  // For using semaphores

#define SHARED_MEM_SIZE 4

// Shared file descriptor used to refer to
// the shared memory object
int shared_fd = -1;

// The pointer to the shared counter
int32_t* counter = NULL;

// The pointer to the shared semaphore
sem_t* semaphore = NULL;

void init_control_mechanism() {
  semaphore = sem_open("/sem0", O_CREAT | O_EXCL, 0600, 1);
  if (semaphore == SEM_FAILED) {
    fprintf(stderr, "ERROR: Opening the semaphore failed: %s\n",
        strerror(errno));
    exit(1);
  }
}

void shutdown_control_mechanism() {
  if (sem_close(semaphore) < 0) {
    fprintf(stderr, "ERROR: Closing the semaphore failed: %s\n",
        strerror(errno));
    exit(1);
  }
  if (sem_unlink("/sem0") < 0) {
    fprintf(stderr, "ERROR: Unlinking failed: %s\n",
        strerror(errno));
    exit(1);
  }
}

void init_shared_resource() {
  // Open the shared memory object
  shared_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
  if (shared_fd < 0) {
    fprintf(stderr, "ERROR: Failed to create shared mem: %s\n",
        strerror(errno));
    exit(1);
  }
  fprintf(stdout, "Shared memory fd is: %d\n", shared_fd);
}

void shutdown_shared_resource() {
  if (shm_unlink("/shm0") < 0) {
    fprintf(stderr, "ERROR: Unlinking failed: %s\n",
        strerror(errno));
    exit(1);
  }
}

void inc_counter() {
  usleep(1);
  sem_wait(semaphore); // Return value should be checked.
  int32_t temp = *counter;
  usleep(1);
  temp++;
  usleep(1);
  *counter = temp;
  sem_post(semaphore); // Return value should be checked.
  usleep(1);
}

int main(int argc, char** argv) {

  // Parent process needs to initialize the shared resource
  init_shared_resource();

  // Parent process needs to initialize the control mechanism
  init_control_mechanism();

  // Allocate and truncate the shared memory region
  if (ftruncate(shared_fd, SHARED_MEM_SIZE * sizeof(char)) < 0) {
    fprintf(stderr, "ERROR: Truncation failed: %s\n",
            strerror(errno));
    return 1;
  }
  fprintf(stdout, "The memory region is truncated.\n");

  // Map the shared memory and initialize the counter
  void* map = mmap(0, SHARED_MEM_SIZE, PROT_WRITE,
                    MAP_SHARED, shared_fd, 0);
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
    fprintf(stdout, "Parent process sees the counter as %d.\n",
        *counter);

    // Wait for the child process to exit
    int status = -1;
    wait(&status);
    fprintf(stdout, "Child process finished with status %d.\n",
        status);
  } else { // The child process
    // Incrmenet the counter
    inc_counter();
    fprintf(stdout, "Child process sees the counter as %d.\n",
        *counter);
  }
  if (munmap(counter, SHARED_MEM_SIZE) < 0) {
    fprintf(stderr, "ERROR: Unmapping failed: %s\n",
            strerror(errno));
    return 1;
  }
  if (close(shared_fd) < 0) {
    fprintf(stderr, "ERROR: Closing the fd filed: %s\n",
        strerror(errno));
    return 1;
  }

  // Only parent process needs to shut down the shared resource
  // and the employed control mechanism
  if (pid) {
    shutdown_shared_resource();
    shutdown_control_mechanism();
  }

  return 0;
}
