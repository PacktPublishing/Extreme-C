// File name: ExtremeC_examples_chapter6_2.cpp
// Description: Definition of the member functions in the Car class

#include <string.h>

#include "ExtremeC_examples_chapter6_2.h"

Car::Car(const char* name) {
  strcpy(this->name, name);
  this->speed = 0.0;
  this->fuel = 0.0;
}

Car::~Car() {
  // Nothing to do
}

void Car::Accelerate() {
  this->speed += 0.05;
  this->fuel -= 1.0;
  if (this->fuel < 0.0) {
    this->fuel = 0.0;
  }
}

void Car::Brake() {
  this->speed -= 0.07;
  if (this->speed < 0.0) {
    this->speed = 0.0;
  }
  this->fuel -= 2.0;
  if (this->fuel < 0.0) {
    this->fuel = 0.0;
  }
}

void Car::Refuel(double amount) {
  this->fuel = amount;
}
