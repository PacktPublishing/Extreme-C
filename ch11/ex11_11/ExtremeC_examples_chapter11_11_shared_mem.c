// File name: ExtremeC_examples_chapter11_11_shared_mem.c
// Description: Implementation of the shared_mem class.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

#define TRUE 1
#define FALSE 0

typedef int32_t bool_t;

typedef struct {
  char* name;
  int shm_fd;
  bool_t owner;
  void* map_ptr;
  char* ptr;
  size_t size;
} shared_mem_t;

shared_mem_t* shared_mem_new() {
  return (shared_mem_t*)malloc(sizeof(shared_mem_t));
}

void shared_mem_delete(shared_mem_t* obj) {
  free(obj->name);
  free(obj);
}

void shared_mem_ctor(shared_mem_t* obj, const char* name, size_t size) {
  obj->size = size;
  obj->name = (char*)malloc(strlen(name) + 1);
  strcpy(obj->name, name);
  obj->shm_fd = shm_open(obj->name, O_RDWR, 0600);
  if (obj->shm_fd >= 0) {
    obj->owner = FALSE;
    printf("The shared memory %s is opened.\n", name);
  } else if (errno == ENOENT) {
    printf("WARN: The shared memory %s does not exist.\n", name);
    obj->shm_fd = shm_open(obj->name, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (obj->shm_fd >= 0) {
      obj->owner = TRUE;
      printf("The shared memory %s is created and opened.\n", name);
    } else {
      fprintf(stderr, "ERROR(%s): Failed to create shared memory: %s\n",
          name, strerror(errno));
      exit(1);
    }
  } else {
      fprintf(stderr, "ERROR(%s): Failed to create shared memory: %s\n",
          name, strerror(errno));
    exit(1);
  }
  if (obj->owner) {
    if (ftruncate(obj->shm_fd, obj->size) < 0) {
      fprintf(stderr, "ERROR(%s): Truncation failed: %s\n",
          name, strerror(errno));
      exit(1);
    }
  }
  obj->map_ptr = mmap(0, obj->size, PROT_READ | PROT_WRITE,
      MAP_SHARED, obj->shm_fd, 0);
  if (obj->map_ptr == MAP_FAILED) {
    fprintf(stderr, "ERROR(%s): Mapping failed: %s\n",
        name, strerror(errno));
    exit(1);
  }
  obj->ptr = (char*)obj->map_ptr;
}

void shared_mem_dtor(shared_mem_t* obj) {
  if (munmap(obj->map_ptr, obj->size) < 0) {
    fprintf(stderr, "ERROR(%s): Unmapping failed: %s\n",
        obj->name, strerror(errno));
    exit(1);
  }
  if (close(obj->shm_fd) < 0) {
    fprintf(stderr, "ERROR(%s): Closing the shared memory fd filed: %s\n",
        obj->name, strerror(errno));
    exit(1);
  }
  if (obj->owner) {
    if (shm_unlink(obj->name) < 0) {
      fprintf(stderr, "ERROR(%s): Unlinking the shared memory failed: %s\n",
          obj->name, strerror(errno));
      exit(1);
    }
  }
}

char* shared_mem_getptr(shared_mem_t* obj) {
  return obj->ptr;
}

bool_t shared_mem_isowner(shared_mem_t* obj) {
  return obj->owner;
}
