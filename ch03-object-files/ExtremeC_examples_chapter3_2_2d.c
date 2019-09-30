// File name: ExtremeC_examples_chapter3_2_2d.c
// Description: Implement 2d geometry calculations.

#include <math.h>

// We need to include the header file since we want
// to use the types polar_pos_2d_t, cartesian_pos_2d_t,
// etc and the trigonometry functions implemented in
// another source file.
#include "ExtremeC_examples_chapter3_2_geometry.h"

cartesian_pos_2d_t convert_to_2d_cartesian_pos(
        const polar_pos_2d_t* polar_pos) {
  cartesian_pos_2d_t result;
  result.x = polar_pos->length * cos_deg(polar_pos->theta);
  result.y = polar_pos->length * sin_deg(polar_pos->theta);
  return result;
}

polar_pos_2d_t convert_to_2d_polar_pos(
        const cartesian_pos_2d_t* cartesian_pos) {
  polar_pos_2d_t result;
  result.length = sqrt(cartesian_pos->x * cartesian_pos->x +
    cartesian_pos->y * cartesian_pos->y);
  result.theta =
      to_degree(atan(cartesian_pos->y / cartesian_pos->x));
  return result;
}
