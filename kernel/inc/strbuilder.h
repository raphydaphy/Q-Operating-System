#ifndef STRBUILD_H
#define STRBUILD_H

#include "list.h"
#include "math.h"
#include "dynsto.h"
#include "charUtils.h"
#include "stringUtils.h"

typedef struct {
    string prevTxt; // like a backup...
    uint32 size; // Should be same as ilist.size
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

#define strbuilder_insert(stb, str, i) \
    strbuilder_inserts(stb, str, i)

void strbuilder_inserts(strbuilder_t*, string, uint32);

void strbuilder_insertc(strbuilder_t*, char, uint32);

#define strbuilder_insertf(stb, f, i) \
    strbuilder_insert(stb, ftos(f), i)

#define strbuilder_inserti(stb, i, index) \
    strbuilder_insert(stb, itos(i), index)

#define strbuilder_replace(stb, str, i) \
    strbuilder_replaces(stb, str, i)

void strbuilder_replaces(strbuilder_t*, string, uint32);

void strbuilder_replacec(strbuilder_t*, char, uint32);

#define strbuilder_replacef(stb, f, i) \
    strbuilder_replace(stb, ftos(f), i)

#define strbuilder_replacei(stb, i, index) \
    strbuilder_replace(stb, itos(i), index)

string strbuilder_tostr(strbuilder_t);

string strbuilder_substr(strbuilder_t, uint32, uint32);

char strbuilder_head(strbuilder_t);

char strbuilder_tail(strbuilder_t);

char strbuilder_charAt(strbuilder_t, uint32);

string strbuilder_delete(strbuilder_t*, uint32, uint32);

char strbuilder_rmchar(strbuilder_t*, uint32);

void strbuilder_rmOuter(strbuilder_t*, uint32, uint32);

string strbuilder_clear(strbuilder_t*);

void strbuilder_destroy(strbuilder_t*);

void strbuilder_trim(strbuilder_t*);

void strbuilder_flip(strbuilder_t*);

bool strbuilder_contains(strbuilder_t, string);

uint32 strbuilder_indexOf(strbuilder_t, string);

uint32 strbuilder_indexFrom(strbuilder_t, string, uint32);

#endif
