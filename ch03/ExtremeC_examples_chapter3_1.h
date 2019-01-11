// File name: ExtremeC_examples_chapter3_1.h
// Description: Contains the declarations needed for the function 'avg'

#ifndef EXTREMEC_EXAMPLES_CHAPTER_3_1_H
#define EXTREMEC_EXAMPLES_CHAPTER_3_1_H

// Enumeration declaration
typedef enum {
  NONE,
  NORMAL,
  SQUARED
} average_type_t;

// Function declaration
double avg(int*, int, average_type_t);

#endif
