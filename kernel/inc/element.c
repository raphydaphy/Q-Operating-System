#include "element.h"

bool cmpElement_t(element_t a, element_t b) {
    if (a.strdata != NULL) {
        if (b.strdata != NULL) {
            return strEql(a.strdata, b.strdata);
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

