// File name: ExtremeC_examples_chapter8_2_main.c
// Description: Main scenario

#include <stdio.h>
#include <stdlib.h>

#include "ExtremeC_examples_chapter8_2_person.h"
#include "ExtremeC_examples_chapter8_2_student.h"

int main(int argc, char** argv) {
  // Create and construct the student object
  struct student_t* student = student_new();
  student_ctor(student, "John", "Doe",
          1987, "TA5667", 134);

  // Now, we use person's behavior functions to
  // read person's attributes from the student object
  char buffer[32];

  // Upcasting to a pointer of parent type
  struct person_t* person_ptr = (struct person_t*)student;

  person_get_first_name(person_ptr, buffer);
  printf("First name: %s\n", buffer);

  person_get_last_name(person_ptr, buffer);
  printf("Last name: %s\n", buffer);

  printf("Birth year: %d\n", person_get_birth_year(person_ptr));

  // Now, we read the attributes specific to the student object.
  student_get_student_number(student, buffer);
  printf("Student number: %s\n", buffer);

  printf("Passed credits: %d\n",
          student_get_passed_credits(student));

  // Destruct and free the student object
  student_dtor(student);
  free(student);

  return 0;
}
