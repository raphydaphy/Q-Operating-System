#include "element.h"

static inline bool __hashDigit(int v, uint8 type)
{
    return ((v % 10) ^ type) == 0;
}

inline bool eqlElement_t(element_t a, element_t b) {
    return cmpElement_t(a, b) == 0;
}

// Compare two element_t's. Should return -1 if
// a.hash < b.hash, 0 if they are equal or 1 otherwise.
int8 cmpElement_t(element_t a, element_t b) {
    if (a.hash == b.hash) return 0;
    if (__hashDigit(a.hash, HASH_STR) && __hashDigit(b.hash, HASH_STR)) {
        return a.hash < b.hash ? -1 : 1;
    }
    if (__hashDigit(a.hash, HASH_INT) && __hashDigit(b.hash, HASH_INT)) {
        return a.hash < b.hash ? -1 : 1;
    }
    if (__hashDigit(a.hash, HASH_FLT) && __hashDigit(b.hash, HASH_FLT)) {
        return a.hash < b.hash ? -1 : 1;
    }
    if (__hashDigit(a.hash, HASH_CHR) && __hashDigit(b.hash, HASH_CHR)) {
        return a.hash < b.hash ? -1 : 1;
    }
    return 1; // Otherwise assume a.hash > b.hash
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
    int tmp;
    switch (e.ctype) {
    case STR:
        tmp = stoc(e.udata.strdata) * 10 + HASH_STR;
        break;
    case INT:
        tmp = e.udata.intdata * 10 + HASH_INT;
        break;
    case FLT:
        // Floats are converted TWICE!!!
        tmp = stoc(ftos(e.udata.floatdata)) * 10 + HASH_FLT;
        break;
    case CHR:
        tmp = e.udata.chardata * 10 + HASH_CHR;
        break;
    case NONE:
    default:
        tmp = HASH_BAD;
        break;
    }
    return tmp;
}

