// File name: ExtremeC_examples_chapter7_2_player.h
// Description: Declares the public API of the class Player

#ifndef EXTREME_C_EXAMPLES_CHAPTER_7_2_PLAYER_H
#define EXTREME_C_EXAMPLES_CHAPTER_7_2_PLAYER_H

// Type forward declarations
struct player_t;
struct gun_t;

// Memory allocator
struct player_t* player_new();

// Constructor
void player_ctor(struct player_t*, const char*);

// Destructor
void player_dtor(struct player_t*);

// Behavior functions
void player_pickup_gun(struct player_t*, struct gun_t*);
void player_shoot(struct player_t*);
void player_drop_gun(struct player_t*);

#endif
