#include "strbuilder.h"

strbuilder_t strbuilder_init() {
    strbuilder_t tmp;
    tmp.prevTxt = "";
    tmp.ilist = list_init();
    tmp.ilist.autoShrink = true;
    return tmp;
}

void strbuilder_appendc(strbuilder_t* stb, char c) {
    list_addc(&(stb->ilist), c);
}

void strbuilder_appends(strbuilder_t* stb, string str) {
    do
        list_addc(&(stb->ilist), *str++);
    while (*str != 0);
}

string strbuilder_tostr(strbuilder_t stb) {
    uint32 strlen = stb.ilist.size;
    string msg = (string) kmalloc((strlen) * sizeof(char));
    uint32 i = 0;
    for(i = 0; i < strlen; i++) {
        msg[i] = stb.ilist.data[i].chardata;
    }
    msg[i] = '\0'; // Strings are null terminated!
    return msg;
}

void strbuilder_destroy(strbuilder_t* stb) {
    list_destroy(&(stb->ilist));
    stb->prevTxt = "";
}

