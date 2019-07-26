// File name: ExtremeC_examples_chapter8_4_duck.c
// Description: Private defintions of the class duck

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ExtremeC_examples_chapter8_4_animal.h"
#include "ExtremeC_examples_chapter8_4_animal_p.h"

typedef struct {
  animal_t animal;
} duck_t;

// Define a new behavior for the duck's sound
void __duck_sound(void* ptr) {
  animal_t* animal = (animal_t*)ptr;
  printf("%s: Quacks\n", animal->name);
}

// Memory allocator
duck_t* duck_new() {
  return (duck_t*)malloc(sizeof(duck_t));
}

// Constructor
void duck_ctor(duck_t* duck) {
  animal_ctor((struct animal_t*)duck);
  strcpy(duck->animal.name, "Duck");
  // Point to the new behavior function. Overriding
  // is actually happening here.
  duck->animal.sound_func = __duck_sound; 
}

// Destructor
void duck_dtor(duck_t* duck) {
  animal_dtor((struct animal_t*)duck);
}
