// File name: ExtremeC_examples_chapter8_3_student.c
// Description: Private implementation of the class student

#include <stdlib.h>
#include <string.h>

// Public interface of the person class
#include "ExtremeC_examples_chapter8_3_person.h"

//Forward declaration
typedef struct {
  char* student_number;
  unsigned int passed_credits;
  // We have to have a pointer here since the type
  // person_t is incomplete.
  struct person_t* person;
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
  // Allocate memory for the parent object
  student->person = person_new();
  person_ctor(student->person, first_name,
          last_name, birth_year);
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
  person_dtor(student->person);
  // And we need to free the parent object's allocated memory
  free(student->person);
}

// Behavior functions
void student_get_first_name(student_t* student, char* buffer) {
  // We have to use person's behavior function
  person_get_first_name(student->person, buffer);
}

void student_get_last_name(student_t* student, char* buffer) {
  // We have to use person's behavior function
  person_get_last_name(student->person, buffer);
}

unsigned int student_get_birth_year(student_t* student) {
  // We have to use person's behavior function
  return person_get_birth_year(student->person);
}

void student_get_student_number(student_t* student,
                                char* buffer) {
  strcpy(buffer, student->student_number);
}

unsigned int student_get_passed_credits(student_t* student) {
  return student->passed_credits;
}
