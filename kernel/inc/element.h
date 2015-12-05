#ifndef L_ELEMENT_H
#define L_ELEMENT_H

#include "stringUtils.h"
#include "intTypeDefs.h"

typedef enum {
    STR, INT, FLT, CHR, NONE
} etype;

typedef struct {
    union {
        string strdata;
        int intdata;
        float floatdata;
        char chardata;
    } udata;
    etype ctype;
    int hash;
} element_t;

#define HASH_BAD 0
#define HASH_STR 1
#define HASH_INT 2
#define HASH_FLT 3
#define HASH_CHR 4

bool eqlElement_t(element_t, element_t);

int8 cmpElement_t(element_t, element_t);

element_t makeNullElement();

element_t makeIntElement(int);

element_t makeFloatElement(float);

element_t makeCharElement(char);

element_t makeStrElement(string);

int generateHash(element_t);

void rehash(element_t*);

#endif
