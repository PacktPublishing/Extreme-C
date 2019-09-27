// File name: ExtremeC_examples_chapter2_2.c
// Description: Two functions to demonstrate symbols in the object file

int average(int a, int b) {
  return (a + b) / 2;
}

int sum(int* numbers, int count) {
  int sum = 0;
  for (int i = 0; i < count; i++) {
    sum += numbers[i];
  }
  return sum;
}
