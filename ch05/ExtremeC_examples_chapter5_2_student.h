// File name: ExtremeC_examples_chapter5_2_student.h
// Description: Public interface of the student class

#ifndef EXTREME_C_EXAMPLES_CHAPTER_5_2_STUDENT_H
#define EXTREME_C_EXAMPLES_CHAPTER_5_2_STUDENT_H

//Forward declaration
struct student_t;

// Memory allocator
struct student_t* student_new();

// Constructor
void student_ctor(struct student_t*, 
                  const char*  /* first name */, 
                  const char*  /* last name */, 
                  unsigned int /* birth year */,
                  const char*  /* student numebr */,
                  unsigned int /* passed credits */);

// Destructor
void student_dtor(struct student_t*);

// Behavior functions
void student_get_student_number(struct student_t*, char*);
unsigned int student_get_passed_credits(struct student_t*);

#endif
