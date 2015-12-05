#include "strbuilder.h"

strbuilder_t strbuilder_init() {
    strbuilder_t tmp;
    tmp.prevTxt = "";
    tmp.ilist = list_init();
    tmp.ilist.autoShrink = true;
    return tmp;
}

static inline void __backupText(strbuilder_t* stb) {
    stb->prevTxt = strbuilder_tostr(*stb);
}

void strbuilder_appendc(strbuilder_t* stb, char c) {
    __backupText(stb);
    list_addc(&(stb->ilist), c);
}

void strbuilder_appends(strbuilder_t* stb, string str) {
    __backupText(stb);
    do
        list_addc(&(stb->ilist), *str++);
    while (*str != 0);
}

string strbuilder_tostr(strbuilder_t stb) {
    uint32 strlen = stb.ilist.size;
    string msg = (string) kmalloc((strlen) * sizeof(char));
    uint32 i = 0;
    for(i = 0; i < strlen; i++) {
        msg[i] = list_getc(stb.ilist, i);
    }
    msg[i] = '\0'; // Strings are null terminated!
    return msg;

}
void strbuilder_clear(strbuilder_t* stb) {
    __backupText(stb);
    list_clear(&(stb->ilist));
}

void strbuilder_destroy(strbuilder_t* stb) {
    list_destroy(&(stb->ilist));
    stb->prevTxt = "";
}

