// File name: ExtremeC_examples_chapter8_3_main.c
// Description: Main scenario

#include <stdio.h>
#include <stdlib.h>

#include "ExtremeC_examples_chapter8_3_student.h"

int main(int argc, char** argv) {
  // Create and construct the student object
  struct student_t* student = student_new();
  student_ctor(student, "John", "Doe",
          1987, "TA5667", 134);

  // We have to use student's behavior functions because the
  // student pointer is not a person pointer and we cannot
  // access to private parent pointer in the student object.
  char buffer[32];
  student_get_first_name(student, buffer);
  printf("First name: %s\n", buffer);

  student_get_last_name(student, buffer);
  printf("Last name: %s\n", buffer);

  printf("Birth year: %d\n", student_get_birth_year(student));

  student_get_student_number(student, buffer);
  printf("Student number: %s\n", buffer);

  printf("Passed credits: %d\n",
          student_get_passed_credits(student));

  // Destruct and free the student object
  student_dtor(student);
  free(student);

  return 0;
}
