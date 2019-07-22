// File name: ExtremeC_examples_chapter6_2_main.cpp
// Description: Main function

#include "ExtremeC_examples_chapter6_2.h"

// Main function
int main(int argc, char** argv) {

  // Create the object variable and call the constructor
  Car car("Renault");

  // Main algorithm
  car.Refuel(1000.0);
  while (car.fuel > 0) {
    if (car.speed < 80) {
      car.Accelerate();
    } else {
      car.Brake();
    }
  }

  while (car.speed > 0) {
    car.Brake();
  }

  // When leaving the function, the object `car` gets
  // desructed automatically.
  return 0;
}
