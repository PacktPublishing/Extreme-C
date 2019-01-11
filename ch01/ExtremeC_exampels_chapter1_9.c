// File name: ExtremeC_exampels_chapter1_9.c
// Description: Example 1.9

int main(int argc, char** argv) {
  int var = 100;
  int* ptr = 0;
  ptr = &var;
  *ptr = 200;
  return 0;
}
