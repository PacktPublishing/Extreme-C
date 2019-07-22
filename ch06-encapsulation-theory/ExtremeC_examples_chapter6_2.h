// File name: ExtremeC_examples_chapter6_2.h
// Description: Declaration of the class Car

#ifndef EXTREME_C_EXAMPLES_CHAPTER_6_2_H
#define EXTREME_C_EXAMPLES_CHAPTER_6_2_H
 
class Car {
public:
  // Constructor
  Car(const char*);
  // Destructor
  ~Car();

  void Accelerate();
  void Brake();
  void Refuel(double);

  // Data Members (Attributes in C)
  char name[32];
  double speed;
  double fuel;
};

#endif
