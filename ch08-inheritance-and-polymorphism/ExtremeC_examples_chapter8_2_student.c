// File name: ExtremeC_examples_chapter8_2_student.c
// Description: Private implementation of the class student

#include <stdlib.h>
#include <string.h>

#include "ExtremeC_examples_chapter8_2_person.h"

// person_t is defined in the following header
// file and we need it here.
#include "ExtremeC_examples_chapter8_2_person_p.h"

//Forward declaration
typedef struct {
  // Here, we inherit all attributes from the person class and
  // also we can use all of its behavior functions because of
  // this nesting.
  person_t person;
  char* student_number;
  unsigned int passed_credits;
} student_t;

// Memory allocator
student_t* student_new() {
  return (student_t*)malloc(sizeof(student_t));
}

// Constructor
void student_ctor(student_t* student, 
                  const char* first_name, 
                  const char* last_name, 
                  unsigned int birth_year,
                  const char* student_number,
                  unsigned int passed_credits) {
  // Call the constructor of the parent class
  person_ctor((struct person_t*)student,
          first_name, last_name, birth_year);
  student->student_number = (char*)malloc(16 * sizeof(char));
  strcpy(student->student_number, student_number);
  student->passed_credits = passed_credits;
}

// Destructor
void student_dtor(student_t* student) {
  // We need to destruct the child object first.
  free(student->student_number);
  // Then, we need to call the destructor function
  // of the parent class
  person_dtor((struct person_t*)student);
}

// Behavior functions
void student_get_student_number(student_t* student, 
                                char* buffer) {
  strcpy(buffer, student->student_number);
}

unsigned int student_get_passed_credits(student_t* student) {
  return student->passed_credits;
}
