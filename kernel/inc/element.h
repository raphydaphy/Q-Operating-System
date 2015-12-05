#ifndef L_ELEMENT_H
#define L_ELEMENT_H

#include "stringUtils.h"
#include "intTypeDefs.h"

typedef enum {
    STR = 1,
    INT = 2,
    FLT = 3,
    CHR = 4,
    NONE = 0
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

string etos(element_t);

int etoi(element_t);

float etof(element_t);

char etoc(element_t);

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
