// File name: ExtremeC_examples_chapter7_2_gun.c
// Description: Implementation of the class Gun

#include <stdlib.h>

typedef int bool_t;

// Attribute structure
typedef struct {
  int bullets;
} gun_t;

// Memory allocator
gun_t* gun_new() {
  return (gun_t*)malloc(sizeof(gun_t));
}

// Constructor
void gun_ctor(gun_t* gun, int initial_bullets) {
  gun->bullets = 0;
  if (initial_bullets > 0) {
    gun->bullets = initial_bullets;
  }
}

// Destructor
void gun_dtor(gun_t* gun) {
  // Nothing to do
}

// Behavior functions
bool_t gun_has_bullets(gun_t* gun) {
  return (gun->bullets > 0);
}

void gun_trigger(gun_t* gun) {
  gun->bullets--;
}

void gun_refill(gun_t* gun) {
  gun->bullets = 7;
}
