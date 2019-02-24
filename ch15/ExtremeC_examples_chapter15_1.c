// File name: ExtremeC_examples_chapter15_1.c
// Description: Demonstrate how to use a named semaphore to protect a
//              shared memory based counter.

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

#define SH_SIZE 4

// The pointer to the shared counter
int32_t* counter = NULL;

// The shared semaphore
sem_t* semaphore = NULL;

void init_control_mechanism() {
  // This semaphore allows only one process to enter the critical section
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
    fprintf(stderr, "ERROR: Unlinking the semaphore failed: %s\n",
        strerror(errno));
    exit(1);
  }
}

int init_shared_resource() {
  // Open the shared memory object
  int shm_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
  if (shm_fd < 0) {
    fprintf(stderr, "ERROR: Failed to create shared memory: %s\n",
        strerror(errno));
    exit(1);
  }
  fprintf(stdout, "Shared memory is created with fd: %d\n", shm_fd);
  return shm_fd;
}

void shutdown_shared_resource() {
  if (shm_unlink("/shm0") < 0) {
    fprintf(stderr, "ERROR: Unlinking the shared memory failed: %s\n",
        strerror(errno));
    exit(1);
  }
}

void inc_counter() {
  usleep(1);
  sem_wait(semaphore);
  int32_t temp = *counter;
  usleep(1);
  temp++;
  usleep(1);
  *counter = temp;
  sem_post(semaphore);
  usleep(1);
}

int main(int argc, char** argv) {

  // Parent process needs to initialize the shared resource
  int fd = init_shared_resource();

  // Parent process needs to initialize the control mechanism
  init_control_mechanism();

  // Allocate and truncate the shared memory region
  if (ftruncate(fd, SH_SIZE * sizeof(char)) < 0) {
    fprintf(stderr, "ERROR: Truncation failed: %s\n", strerror(errno));
    return 1;
  }
  fprintf(stdout, "The memory region is truncated.\n");

  // Map the shared memory and initialize the counter
  void* map = mmap(0, SH_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
  if (map == MAP_FAILED) {
    fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
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
  if (munmap(counter, SH_SIZE) < 0) {
    fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
    return 1;
  }
  if (close(fd) < 0) {
    fprintf(stderr, "ERROR: Closing the shared memory fd filed: %s\n",
        strerror(errno));
    return 1;
  }

  // Only parent process needs to shutdown the shared resource and
  // the employed control mechanism
  if (pid) {
    shutdown_shared_resource();
    shutdown_control_mechanism();
  }

  return 0;
}
