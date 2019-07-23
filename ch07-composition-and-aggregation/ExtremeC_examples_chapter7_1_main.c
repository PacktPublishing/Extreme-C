// File name: ExtremeC_examples_chapter7_1_main.c
// Description: Main scenario using a car object

#include <stdio.h>
#include <stdlib.h>

#include "ExtremeC_examples_chapter7_1_car.h"

int main(int argc, char** argv) {

  // Allocate memory for the car object
  struct car_t *car = car_new();

  // Construct the car object
  car_ctor(car);

  printf("Engine temperature before starting the car: %f\n",
          car_get_engine_temperature(car));
  car_start(car);
  printf("Engine temperature after starting the car: %f\n",
          car_get_engine_temperature(car));
  car_stop(car);
  printf("Engine temperature after stopping the car: %f\n",
          car_get_engine_temperature(car));

  // Destruct the car object
  car_dtor(car);

  // Free the memory allocated for the car object
  free(car);

  return 0;
}
