// File name: ExtremeC_examples_chapter8_4_animal.c
// Description: Private definition of the behavior functions
//              of the animal class

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ExtremeC_examples_chapter8_4_animal_p.h"

// Default definition of the animal_sound at the parent level
void __animal_sound(void* this_ptr) {
  animal_t* animal = (animal_t*)this_ptr;
  printf("%s: Beeeep\n", animal->name);
}

// Memory allocator
animal_t* animal_new() {
  return (animal_t*)malloc(sizeof(animal_t));
}

// Constructor
void animal_ctor(animal_t* animal) {
  animal->name = (char*)malloc(10 * sizeof(char));
  strcpy(animal->name, "Animal");
  // Set the function pointer to point to the default definition
  animal->sound_func = __animal_sound;
}

// Destructor
void animal_dtor(animal_t* animal) {
  free(animal->name);
}

// Behavior functions
void animal_get_name(animal_t* animal, char* buffer) {
  strcpy(buffer, animal->name);
}

void animal_sound(animal_t* animal) {
  // Call the function which is pointed by the fucntion pointer.
  animal->sound_func(animal);
}
