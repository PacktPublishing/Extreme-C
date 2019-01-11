// File name: ExtremeC_examples_chapter5_2_main.c
// Description: Main scenario

#include <stdio.h>
#include <stdlib.h>

#include "ExtremeC_examples_chapter5_2_person.h"
#include "ExtremeC_examples_chapter5_2_student.h"

int main(int argc, char** argv) {
  // Create and construct the student object
  struct student_t* student = student_new();
  student_ctor(student, "Thomas", "Anderson", 1987, "TA5667", 134);
  
  // Now, we use person's behavior functions to read person's attributes from
  // the student object
  char buffer[32];
  person_get_first_name((struct person_t*)student, buffer);
  printf("First name: %s\n", buffer);
  
  person_get_last_name((struct person_t*)student, buffer);
  printf("Last name: %s\n", buffer);
  
  printf("Birth year: %d\n", person_get_birth_year((struct person_t*)student));
  
  // Now, we read the attributes specific to the student object.
  student_get_student_number(student, buffer);
  printf("Student number: %s\n", buffer);
  
  printf("Passed credits: %d\n", student_get_passed_credits(student));
  
  // Destruct and free the student object
  student_dtor(student);
  free(student);
  
  return 0;
}
