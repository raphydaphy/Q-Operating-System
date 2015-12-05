#ifndef STRBUILD_H
#define STRBUILD_H

#include "list.h"
#include "math.h"
#include "dynsto.h"
#include "stringUtils.h"

typedef struct {
    string prevTxt; // like a backup...
    list_t ilist; // list_t is the internal engine!
} strbuilder_t;

strbuilder_t strbuilder_init();

#define strbuilder_append(stb, str) \
    strbuilder_appends(stb, str)

void strbuilder_appendc(strbuilder_t*, char);

void strbuilder_appends(strbuilder_t*, string);

#define strbuilder_appendf(stb, f) \
    strbuilder_append(stb, ftos(f))

#define strbuilder_appendi(stb, i) \
    strbuilder_append(stb, itos(i))

string strbuilder_tostr(strbuilder_t);

string strbuilder_substr(strbuilder_t, uint32, uint32);

void strbuilder_delete(strbuilder_t*, uint32, uint32);

void strbuilder_clear(strbuilder_t*);

void strbuilder_destroy(strbuilder_t*);

#endif
