// File name: ExtremeC_examples_chapter8_2_person.h
// Description: Public interface of the person class

#ifndef EXTREME_C_EXAMPLES_CHAPTER_8_2_PERSON_H
#define EXTREME_C_EXAMPLES_CHAPTER_8_2_PERSON_H

// Forward declaration
struct person_t;

// Memory allocator
struct person_t* person_new();

// Constructor
void person_ctor(struct person_t*, 
                 const char*  /* first name */, 
                 const char*  /* last name */, 
                 unsigned int /* birth year */);

// Destructor
void person_dtor(struct person_t*);

// Behavior functions
void person_get_first_name(struct person_t*, char*);
void person_get_last_name(struct person_t*, char*);
unsigned int person_get_birth_year(struct person_t*);

#endif
