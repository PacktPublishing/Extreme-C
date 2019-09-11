// File name: ExtremeC_examples_chapter9_4_list.h
// Description: Public interface of the list class

#ifndef EXTREME_C_EXAMPLES_CHAPTER_9_4_LIST_H
#define EXTREME_C_EXAMPLES_CHAPTER_9_4_LIST_H

struct list_t;

// Creates an empty list
struct list_t* list_empty();

struct list_t* list_add(struct list_t*, int);
void list_print(struct list_t*);

#endif
