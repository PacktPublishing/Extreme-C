// File name: ExtremeC_examples_chapter18_4_shared_int32.h
// Description: Declaration of the shared_int32 class.

#include <stdint.h>

// Forward declaration
struct shared_int32_t;

struct shared_int32_t* shared_int32_new();
void shared_int32_delete(struct shared_int32_t* obj);

void shared_int32_ctor(struct shared_int32_t* obj,
                       const char* name);
void shared_int32_dtor(struct shared_int32_t* obj);

void shared_int32_setvalue(struct shared_int32_t* obj,
                           int32_t value);
void shared_int32_setvalue_ifowner(struct shared_int32_t* obj,
                                   int32_t value);
int32_t shared_int32_getvalue(struct shared_int32_t* obj);
