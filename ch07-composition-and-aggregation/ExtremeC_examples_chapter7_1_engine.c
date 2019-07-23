// File name: ExtremeC_examples_chapter4_4_engine.c
// Description: Implementation of the class Engine

#include <stdlib.h>

typedef enum {
  ON,
  OFF
} state_t;

typedef struct {
  state_t state;
  double temperature;
} engine_t;

// Memory allocator
engine_t* engine_new() {
  return (engine_t*)malloc(sizeof(engine_t));
}

// Constructor
void engine_ctor(engine_t* engine) {
  engine->state = OFF;
  engine->temperature = 15;
}

// Destructor
void engine_dtor(engine_t* engine) {
  // Nothing to do
}

// Behavior functions
void engine_turn_on(engine_t* engine) {
  if (engine->state == ON) {
    return;
  }
  engine->state = ON;
  engine->temperature = 75;
}

void engine_turn_off(engine_t* engine) {
  if (engine->state == OFF) {
    return;
  }
  engine->state = OFF;
  engine->temperature = 15;
}

double engine_get_temperature(engine_t* engine) {
  return engine->temperature;
}
