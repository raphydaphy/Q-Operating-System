#ifndef SET_H
#define SET_H

#include "dynsto.h"

// Sets Always Autoshrink

typedef struct {
    element_t* data;
    uint32 capt;
    uint32 size;
} set_t;

set_t set_init();

#define set_add(s, e) \
    set_adds(s, e)

void set_adds(set_t*, string);

void set_addi(set_t*, int);

void set_addf(set_t*, float);

void set_addc(set_t*, char);

#define set_get(s, i) \
    set_gets(s, i)

string set_gets(set_t, uint32);

int set_geti(set_t, uint32);

float set_getf(set_t, uint32);

char set_getc(set_t, uint32);

uint32 set_indexOf(set_t*, element_t);

bool set_contains(set_t*, element_t);

void set_destroy(set_t*);
#endif
