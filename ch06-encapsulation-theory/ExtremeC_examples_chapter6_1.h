// File name: ExtremeC_examples_chapter6_1.h
// Description: Declarations for attribute sturcture
//              and behavior functions

#ifndef EXTREME_C_EXAMPLES_CHAPTER_6_1_H
#define EXTREME_C_EXAMPLES_CHAPTER_6_1_H

// This structure keeps all the attributes 
// related to a car object
typedef struct {
  char name[32];
  double speed;
  double fuel;
} car_t;

// These function declarations are the bevahiors of a car object
void car_construct(car_t*, const char*);
void car_destruct(car_t*);
void car_accelerate(car_t*);
void car_brake(car_t*);
void car_refuel(car_t*, double);

#endif
