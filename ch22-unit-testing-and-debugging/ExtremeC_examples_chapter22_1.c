// File name: ExtremeC_examples_chapter22_1.c
// Description: Definisitons of the declared functions

#include "ExtremeC_examples_chapter22_1.h"

int64_t next_even_number() {
  static int feed = -2;
  feed += 2;
  if (feed >= 10) {
    feed = 0;
  }
  return feed;
}

int64_t calc_factorial(int64_feed_t feed) {
  int64_t fact = 1;
  int64_t number = feed();
  for (int64_t i = 1; i <= number; i++) {
    fact *= i;
  }
  return fact;
}
