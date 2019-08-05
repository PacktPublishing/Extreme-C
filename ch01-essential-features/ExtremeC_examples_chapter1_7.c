// File name: ExtremeC_exampels_chapter1_7.c
// Description: Example 1.7

#define CONDITION1

int main(int argc, char** argv) {
#ifdef CONDITION
  int i = 0;
  i++;
#endif
  int j= 0;  
  return 0;
}
