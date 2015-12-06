#ifndef LIST_H
#define LIST_H

#include "dynsto.h"

typedef struct {
    element_t* data;
    uint32 capt;
    uint32 size;
    bool autoShrink; // False on default...
    uint32 autoShrinkTrigger;
} list_t;

list_t list_init();

list_t list_init_s(uint32);

#define list_add(lst, e) \
    list_adds(lst, e)

void list_adds(list_t*, string);

void list_addi(list_t*, int);

void list_addf(list_t*, float);

void list_addc(list_t*, char);

#define list_insert(lst, e) \
    list_inserts(lst, e)

void list_inserts(list_t*, string, uint32);

void list_inserti(list_t*, int, uint32);

void list_insertf(list_t*, float, uint32);

void list_insertc(list_t*, char, uint32);

#define list_get(lst, i) \
    list_gets(lst, i)

string list_gets(list_t, uint32);

int list_geti(list_t, uint32);

float list_getf(list_t, uint32);

char list_getc(list_t, uint32);

#define list_head(lst) \
    list_heads(lst)

#define list_heads(lst) \
    list_gets(lst, 0)

#define list_headi(lst) \
    list_geti(lst, 0)

#define list_headf(lst) \
    list_getf(lst, 0)

#define list_headc(lst) \
    list_getc(lst, 0)

#define list_tail(lst) \
    list_tails(lst)

#define list_tails(lst) \
    list_gets(lst, lst.size - 1)

#define list_taili(lst) \
    list_geti(lst, lst.size - 1)

#define list_tailf(lst) \
    list_getf(lst, lst.size - 1)

#define list_tailc(lst) \
    list_getc(lst, lst.size - 1)

element_t list_remove(list_t*, uint32);

#define list_pop(lst) \
    list_remove(lst, lst->size)

#define list_shift(lst) \
    list_remove(lst, 0)

element_t list_replaces(list_t*, uint32, string);

element_t list_replacei(list_t*, uint32, int);

element_t list_replacef(list_t*, uint32, float);

element_t list_replacec(list_t*, uint32, char);

#define list_replace(lst, i, s) \
    list_replaces(lst, i, s)

void list_shrink(list_t*);

void list_clear(list_t*);

uint32 list_indexOf(list_t*, element_t);

bool list_contains(list_t*, element_t);

void list_flip(list_t*);

void list_destroy(list_t*);

#endif
