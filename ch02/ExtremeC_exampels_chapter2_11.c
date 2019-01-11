// File name: ExtremeC_examples_chapter2_11.c
// Description: Example 2.11

int* get_integer() {
  int var = 10;
  return &var;
}

int main(int argc, char** argv) {
  int* ptr = get_integer();
  *ptr = 5;
  return 0;
}
