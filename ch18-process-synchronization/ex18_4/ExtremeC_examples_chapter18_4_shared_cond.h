// File name: ExtremeC_examples_chapter18_4_shared_cond.h
// Description: Declaration of the shared_cond class.

// Forward declaration
struct shared_cond_t;
struct shared_mutex_t;

struct shared_cond_t* shared_cond_new();
void shared_cond_delete(struct shared_cond_t* obj);

void shared_cond_ctor(struct shared_cond_t* obj,
                      const char* name);
void shared_cond_dtor(struct shared_cond_t* obj);

void shared_cond_wait(struct shared_cond_t* obj,
                      struct shared_mutex_t* mutex);
void shared_cond_timedwait(struct shared_cond_t* obj,
                           struct shared_mutex_t* mutex,
                           long int time_nanosec);
void shared_cond_broadcast(struct shared_cond_t* obj);
