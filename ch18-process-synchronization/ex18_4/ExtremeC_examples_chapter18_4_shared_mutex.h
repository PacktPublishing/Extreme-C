// File name: ExtremeC_examples_chapter18_4_shared_mutex.h
// Description: Declaration of the shared_mutex class.

#include <pthread.h>

// Forward declaration
struct shared_mutex_t;

struct shared_mutex_t* shared_mutex_new();
void shared_mutex_delete(struct shared_mutex_t* obj);

void shared_mutex_ctor(struct shared_mutex_t* obj,
                       const char* name);
void shared_mutex_dtor(struct shared_mutex_t* obj);

pthread_mutex_t* shared_mutex_getptr(struct shared_mutex_t* obj);

void shared_mutex_lock(struct shared_mutex_t* obj);
void shared_mutex_unlock(struct shared_mutex_t* obj);

#if !defined(__APPLE__)
void shared_mutex_make_consistent(struct shared_mutex_t* obj);
#endif
