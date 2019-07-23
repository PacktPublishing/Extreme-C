// File name: ExtremeC_examples_chapter7_2_main.c
// Description: The main scenario for the Player and Gun objects

#include <stdio.h>
#include <stdlib.h>

#include "ExtremeC_examples_chapter7_2_player.h"
#include "ExtremeC_examples_chapter7_2_gun.h"

int main(int argc, char** argv) {
  // Create and constructor the gun object
  struct gun_t* gun = gun_new();
  gun_ctor(gun, 3);

  // Create and construct the player object
  struct player_t* player = player_new();
  player_ctor(player, "Billy");

  // Begin the aggregation relation.
  player_pickup_gun(player, gun);

  // Shoot until no bullet is left.
  while (gun_has_bullets(gun)) {
    player_shoot(player);
  }

  // Refill the gun
  gun_refill(gun);

  // Shoot until no bullet is left.
  while (gun_has_bullets(gun)) {
    player_shoot(player);
  }

  // End the aggregation relation.
  player_drop_gun(player);

  // Destruct and free the player object
  player_dtor(player);
  free(player);

  // Destruct and free the gun object
  gun_dtor(gun);
  free(gun);

  return 0;
}
