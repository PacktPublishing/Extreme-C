// File name: ExtremeC_exampels_chapter2_7.c
// Description: Example 2.7

#include <stdio.h>
#include <stdlib.h>

void print_memory() {
#ifdef LINUX
  FILE* fd = fopen("/proc/self/maps", "r");
  if (!fd) {
    printf("Could not open maps file.\n");
    exit(1);
  }
  char line[1024];
  while (!feof(fd)) {
    fgets(line, 1024, fd);
    printf("> %s", line);
  }
  fclose(fd);
#endif
}

int main(int argc, char**argv) {
  print_memory();
  return 0;
}
