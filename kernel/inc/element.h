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

bool cmpElement_t(element_t, element_t);

#endif
