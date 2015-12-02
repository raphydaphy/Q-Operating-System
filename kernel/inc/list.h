#ifndef LIST_H
#define LIST_H

#include "kheap.h"
#include "byteUtils.h"
#include "stringUtils.h"
#include "intTypeDefs.h"

#define GROWTH_FACTOR 16

typedef struct {
    string* data;
    uint32 capt;
    uint32 size;
    bool autoShrink; // False on default...
    uint32 autoShrinkTrigger;
} list_t;

list_t list_init();

list_t list_init_s(uint32);

void list_add(list_t*, string);

void list_pop(list_t*);

void list_shift(list_t*);

void list_remove(list_t*, uint32);

void list_replace(list_t*, uint32, string);

void list_shrink(list_t*);

void list_resize(list_t*, uint32);

void list_clear(list_t*);

uint32 list_indexOf(list_t*, string);

bool list_contains(list_t*, string);

void list_destroy(list_t*);

#endif
