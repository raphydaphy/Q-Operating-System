#include "element.h"

static inline bool __hashDigit(int v, etype type) {
    return ((v % 10) ^ type) == 0;
}

inline bool eqlElement_t(element_t a, element_t b) {
    return cmpElement_t(a, b) == 0;
}

#define cmpHashType(a, b, htype) \
    (__hashDigit(a.hash, htype) && __hashDigit(b.hash, htype))

// Compare two element_t's. Should return -1 if
// a.hash < b.hash, 0 if they are equal or 1 otherwise.
int8 cmpElement_t(element_t a, element_t b) {
    if (a.hash == b.hash) return 0;
    if (cmpHashType(a, b, STR)) {
        return strcmp(a.udata.strdata, b.udata.strdata);
    }
    if (cmpHashType(a, b, INT)) {
        return a.udata.intdata < b.udata.intdata ? -1 : 1;
    }
    if (cmpHashType(a, b, FLT)) {
        return a.udata.floatdata < b.udata.floatdata ? -1 : 1;
    }
    if (cmpHashType(a, b, CHR)) {
        return a.udata.chardata < b.udata.chardata ? -1 : 1;
    }
    return 1; // Otherwise assume a.hash > b.hash
}

inline string etos(element_t e) {
    if (e.ctype == STR)
        return e.udata.strdata;
    return "";
}

inline int etoi(element_t e) {
    if (e.ctype == INT)
        return e.udata.intdata;
    return 0;
}

inline float etof(element_t e) {
    if (e.ctype == FLT)
        return e.udata.floatdata;
    return 0;
}

inline char etoc(element_t e) {
    if (e.ctype == CHR)
        return e.udata.chardata;
    return '\0';
}

element_t makeNullElement() {
    element_t tmp;
    tmp.ctype = NONE;
    return tmp;
}

element_t makeIntElement(int v) {
    element_t tmp;
    tmp.udata.intdata = v;
    tmp.ctype = INT;
    rehash(&tmp);
    return tmp;
}

element_t makeFloatElement(float v) {
    element_t tmp;
    tmp.udata.floatdata = v;
    tmp.ctype = FLT;
    rehash(&tmp);
    return tmp;
}

element_t makeStrElement(string v) {
    element_t tmp;
    tmp.udata.strdata = v;
    tmp.ctype = STR;
    rehash(&tmp);
    return tmp;
}

element_t makeCharElement(char v) {
    element_t tmp;
    tmp.udata.chardata = v;
    tmp.ctype = CHR;
    rehash(&tmp);
    return tmp;
}

inline void rehash(element_t* e) {
    e->hash = generateHash(*e);
}

int generateHash(element_t e) {
    switch (e.ctype) {
    case STR:
        return stoc(e.udata.strdata) * 10 + STR;
    case INT:
        return e.udata.intdata * 10 + INT;
    case FLT:
        // Floats are converted TWICE!!!
        return stoc(ftos(e.udata.floatdata)) * 10 + FLT;
    case CHR:
        return e.udata.chardata * 10 + CHR;
    case NONE:
    default:
        return NONE;
    }
}

