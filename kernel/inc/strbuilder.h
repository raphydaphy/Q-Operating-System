#ifndef STRBUILD_H
#define STRBUILD_H

#include "list.h"
#include "dynsto.h"

typedef struct {
    string prevTxt; // like a backup...
    list_t ilist; // list_t is the internal engine!
} strbuilder_t;

strbuilder_t strbuilder_init();

void strbuilder_appendc(strbuilder_t*, char);

void strbuilder_appends(strbuilder_t*, string);

void list_destroy(strbuilder_t*);

#endif
