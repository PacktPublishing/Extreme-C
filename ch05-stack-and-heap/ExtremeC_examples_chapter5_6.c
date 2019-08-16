// File name: ExtremeC_examples_chapter5_6.c
// Description: Example 5.6

#include <stdio.h>  // For printf function
#include <stdlib.h> // For heap memory functions
#include <string.h> // For strcmp function

void fill(int* matrix, int rows, int columns) {
  int counter = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      *(matrix + i * columns + j) = counter;
    }
    counter++;
  }
}

void print_matrix(int* matrix, int rows, int columns) {
  int counter = 1;
  printf("Matrix:\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("%d ", *(matrix + i * columns + j));
    }
    printf("\n");
  }
}

void print_flat(int* matrix, int rows, int columns) {
  printf("Flat matrix: ");
  for (int i = 0; i < (rows * columns); i++) {
    printf("%d ", *(matrix + i));
  }
  printf("\n");
}

int friendly_sum(int* matrix, int rows, int columns) {
  int sum = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      sum += *(matrix + i * columns + j);
    }
  }
  return sum;
}


int not_friendly_sum(int* matrix, int rows, int columns) {
  int sum = 0;
  for (int j = 0; j < columns; j++) {
    for (int i = 0; i < rows; i++) {
      sum += *(matrix + i * columns + j);
    }
  }
  return sum;
}

int main(int argc, char** argv) {

  if (argc < 4) {
    printf("Usage: %s [print|friendly-sum|not-friendly-sum] ");
    printf("[number-of-rows] [number-of-columns]\n", argv[0]);
    exit(1);
  }
  char* operation = argv[1];
  int rows = atol(argv[2]);
  int columns = atol(argv[3]);

  int* matrix = (int*)malloc(rows * columns * sizeof(int));
  fill(matrix, rows, columns);

  if (strcmp(operation, "print") == 0) {
    print_matrix(matrix, rows, columns);
    print_flat(matrix, rows, columns);
  }
  else if (strcmp(operation, "friendly-sum") == 0) {
    int sum = friendly_sum(matrix, rows, columns);
    printf("Friendly sum: %d\n", sum);
  }
  else if (strcmp(operation, "not-friendly-sum") == 0) {
    int sum = not_friendly_sum(matrix, rows, columns);
    printf("Not friendly sum: %d\n", sum);
  }
  else {
    printf("FATAL: Not supported operation!\n");
    exit(1);
  }

  free(matrix);
  return 0;
}
