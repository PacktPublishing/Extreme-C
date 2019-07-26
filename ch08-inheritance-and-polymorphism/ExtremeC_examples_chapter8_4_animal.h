// File name: ExtremeC_examples_chapter8_4_animal.h
// Description: Public interface of the animal class

#ifndef EXTREME_C_EXAMPLES_CHAPTER_8_4_ANIMAL_H
#define EXTREME_C_EXAMPLES_CHAPTER_8_4_ANIMAL_H

// Forward declaration
struct animal_t;

// Memory allocator
struct animal_t* animal_new();

// Constructor
void animal_ctor(struct animal_t*);

// Destructor
void animal_dtor(struct animal_t*);

// Behavior functions
void animal_get_name(struct animal_t*, char*);
void animal_sound(struct animal_t*);

#endif
