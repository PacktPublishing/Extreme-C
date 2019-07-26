// File name: ExtremeC_examples_chapter8_4_main.c
// Description: Main scenario which calls the
// polymorphic functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Only public interfaces
#include "ExtremeC_examples_chapter8_4_animal.h"
#include "ExtremeC_examples_chapter8_4_cat.h"
#include "ExtremeC_examples_chapter8_4_duck.h"

int main(int argc, char** argv) {
  struct animal_t* animal = animal_new();
  struct cat_t* cat = cat_new();
  struct duck_t* duck = duck_new();

  animal_ctor(animal);
  cat_ctor(cat);
  duck_ctor(duck);

  animal_sound(animal);
  animal_sound((struct animal_t*)cat);
  animal_sound((struct animal_t*)duck);

  animal_dtor(animal);
  cat_dtor(cat);
  duck_dtor(duck);

  free(duck);
  free(cat);
  free(animal);
  return 0;
}
