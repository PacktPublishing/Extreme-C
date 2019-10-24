// File name: ExtremeC_examples_chapter6_1_main.c
// Description: Main function

#include "ExtremeC_examples_chapter6_1.h"

// Main function
int main(int argc, char** argv) {

  // Create the object variable
  car_t car;
  
  // Construct the object
  car_construct(&car, "Renault");
  
  // Main algorithm
  car_refuel(&car, 1000.0);
  while (car.fuel > 0) {
    if (car.speed < 80) {
      car_accelerate(&car);
    } else {
      car_brake(&car);
    }
  }
  
  while (car.speed > 0) {
    car_brake(&car);
  }
  
  // Destruct the object
  car_destruct(&car);
  
  return 0;
}
