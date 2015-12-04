#include "strbuilder.h"

strbuilder_t strbuilder_init() {
    strbuilder_t tmp;
    tmp.prevTxt = "";
    tmp.ilist = list_init();
    tmp.ilist.autoShrink = true;
    return tmp;
}

void strbuilder_appendc(strbuilder_t* stb, char c) {
    list_addc(&(stb->list), c);
}

void strbuilder_appends(strbuilder_t*, string) {
    list_adds(&(stb->list), c);
}

void list_destroy(strbuilder_t* stb) {
    list_destroy(&(stb->ilist));
    stb.prevTxt = "";
}

