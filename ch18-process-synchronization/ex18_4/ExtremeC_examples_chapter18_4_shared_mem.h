// File name: ExtremeC_examples_chapter18_4_shared_mem.h
// Description: Declaration of the shared_mem class.

// Forward declaration
struct shared_mem_t;

typedef int32_t bool_t;

#define TRUE 1
#define FALSE 0

struct shared_mem_t* shared_mem_new();
void shared_mem_delete(struct shared_mem_t* obj);

void shared_mem_ctor(struct shared_mem_t* obj,
                     const char* name,
                     size_t size);
void shared_mem_dtor(struct shared_mem_t* obj);

char* shared_mem_getptr(struct shared_mem_t* obj);
bool_t shared_mem_isowner(struct shared_mem_t* obj);
void shared_mem_setowner(struct shared_mem_t* obj,
                         bool_t is_owner);
