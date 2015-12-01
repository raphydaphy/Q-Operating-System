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
} list_t;

list_t init_list();

void add(list_t*, string);

void remove(list_t*);

void shrink(list_t*);

void clear(list_t*);

uint32 indexOf(list_t*, string);

bool contains(list_t*, string);

#endif
