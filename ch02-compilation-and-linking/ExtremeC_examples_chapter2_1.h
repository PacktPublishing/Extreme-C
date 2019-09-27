// File name: ExtremeC_examples_chapter2_1.h
// Description: Contains the declaration needed
//              for the 'avg' function

#ifndef EXTREMEC_EXAMPLES_CHAPTER_2_1_H
#define EXTREMEC_EXAMPLES_CHAPTER_2_1_H

typedef enum {
  NONE,
  NORMAL,
  SQUARED
} average_type_t;

// Function declaration
double avg(int*, int, average_type_t);

#endif
