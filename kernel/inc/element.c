#include "element.h"

inline bool cmpElement_t(element_t a, element_t b) {
    return a.hash == b.hash; // Yay!
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

