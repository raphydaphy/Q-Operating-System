#ifndef L_ELEMENT_H
#define L_ELEMENT_H

#include "stringUtils.h"
#include "intTypeDefs.h"

typedef union {
    string strdata;
    int intdata;
    float floatdata;
    char chardata;
} element_t;

#define HASH_BAD 0
#define HASH_STR 1
#define HASH_INT 2
#define HASH_FLT 3
#define HASH_CHR 4

bool cmpElement_t(element_t, element_t);

element_t makeNullElement();

int generateHash(element_t);

#endif
