// File name: ExtremeC_examples_chapter8_4_cat.c
// Description: Private defintions of the class cat

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ExtremeC_examples_chapter8_4_animal.h"
#include "ExtremeC_examples_chapter8_4_animal_p.h"

typedef struct {
  animal_t animal;
} cat_t;

// Define a new behavior for the cat's sound
void __cat_sound(void* ptr) {
  animal_t* animal = (animal_t*)ptr;
  printf("%s: Meow\n", animal->name);
}

// Memory allocator
cat_t* cat_new() {
  return (cat_t*)malloc(sizeof(cat_t));
}

// Constructor
void cat_ctor(cat_t* cat) {
  animal_ctor((struct animal_t*)cat);
  strcpy(cat->animal.name, "Cat");
  // Point to the new behavior function. Overriding
  // is actually happening here.
  cat->animal.sound_func = __cat_sound; 
}

// Destructor
void cat_dtor(cat_t* cat) {
  animal_dtor((struct animal_t*)cat);
}
