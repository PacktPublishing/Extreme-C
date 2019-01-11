// File name: ExtremeC_examples_chapter5_4_cat.h
// Description: Public interface of the cat class

#ifndef EXTREME_C_EXAMPLES_CHAPTER_5_4_CAT_H
#define EXTREME_C_EXAMPLES_CHAPTER_5_4_CAT_H

// Forward declaration
struct cat_t;

// Memory allocator
struct cat_t* cat_new();

// Constructor
void cat_ctor(struct cat_t*);

// Destructor
void cat_dtor(struct cat_t*);

// All behavior functions are inherited from the animal class.

#endif
