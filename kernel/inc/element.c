#include "element.h"

bool cmpElement_t(element_t a, element_t b) {
    if (a.strdata != NULL) {
        if (b.strdata != NULL) {
            return streql(a.strdata, b.strdata);
        }
    } else if (a.intdata != NULL) {
        if (b.intdata != NULL) {
            return a.intdata == b.intdata;
        }
    } else if (a.floatdata != NULL) {
        if (b.floatdata != NULL) {
            return a.floatdata == b.floatdata;
        }
    } else if (a.chardata != NULL) {
        if (b.chardata != NULL) {
            return a.chardata == b.chardata;
        }
    }
    return false;
}

element_t makeNullElement() {
    element_t tmp;
    tmp.intdata = NULL;
    return tmp;
}

int generateHash(element_t e) {
    int tmp = HASH_BAD;
    if (e.strdata != NULL) {
        tmp = stoc(e.strdata) * 10 + HASH_STR;
    } else if (e.intdata != NULL) {
        tmp = e.intdata * 10 + HASH_INT;
    } else if (e.floatdata != NULL) {
        // Floats are converted TWICE!!!
        tmp = stoc(ftos(e.floatdata)) * 10 + HASH_FLT;
    } else if (e.chardata != NULL) {
        tmp = e.chardata * 10 + HASH_CHR;
    }
    return tmp;
}

