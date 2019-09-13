// File name: ExtremeC_examples_chapter8_3_student.h
// Description: Public interface of the student class

#ifndef EXTREME_C_EXAMPLES_CHAPTER_8_3_STUDENT_H
#define EXTREME_C_EXAMPLES_CHAPTER_8_3_STUDENT_H

//Forward declaration
struct student_t;

// Memory allocator
struct student_t* student_new();

// Constructor
void student_ctor(struct student_t*,
                  const char*  /* first name */,
                  const char*  /* last name */,
                  unsigned int /* birth year */,
                  const char*  /* student number */,
                  unsigned int /* passed credits */);

// Destructor
void student_dtor(struct student_t*);

// Behavior functions
void student_get_first_name(struct student_t*, char*);
void student_get_last_name(struct student_t*, char*);
unsigned int student_get_birth_year(struct student_t*);
void student_get_student_number(struct student_t*, char*);
unsigned int student_get_passed_credits(struct student_t*);

#endif
