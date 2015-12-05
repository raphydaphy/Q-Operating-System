#include "strbuilder.h"

strbuilder_t strbuilder_init() {
    strbuilder_t tmp;
    tmp.prevTxt = "";
    tmp.ilist = list_init();
    tmp.ilist.autoShrink = true;
    tmp.size = tmp.ilist.size;
    return tmp;
}

static inline void __backupText(strbuilder_t* stb) {
    stb->prevTxt = strbuilder_tostr(*stb);
}

void strbuilder_appendc(strbuilder_t* stb, char c) {
    __backupText(stb);
    list_addc(&(stb->ilist), c);
    stb->size = stb->ilist.size;
}

void strbuilder_appends(strbuilder_t* stb, string str) {
    __backupText(stb);
    do
        list_addc(&(stb->ilist), *str++);
    while (*str != 0);
    stb->size = stb->ilist.size;
}

static string __vstb_tos(strbuilder_t stb, uint32 l, uint32 h) {
    uint32 strlen = abs(h - l);
    if (strlen > stb.ilist.size) return NULL;
    string msg = (string) kmalloc((strlen) * sizeof(char));
    uint32 i = 0;
    for(i = 0; i < strlen; i++) {
        msg[i] = list_getc(stb.ilist, i);
    }
    msg[i] = '\0'; // Strings are null terminated!
    return msg;
}

string strbuilder_tostr(strbuilder_t stb) {
    return __vstb_tos(stb, 0, stb.ilist.size);
}

string strbuilder_substr(strbuilder_t stb, uint32 l, uint32 h) {
    return __vstb_tos(stb, l, h);
}

char strbuilder_charAt(strbuilder_t stb, uint32 i) {
    return list_getc(stb.ilist, i);
}

void strbuilder_delete(strbuilder_t* stb, uint32 l, uint32 h) {
    __backupText(stb);
    uint32 dist = abs(h - l);
    while(dist-- > 0) {
        list_remove(&(stb->ilist), l);
    }
    stb->size = stb->ilist.size;
}

inline char strbuilder_head(strbuilder_t stb) {
    return strbuilder_charAt(stb, 0);
}

inline char strbuilder_tail(strbuilder_t stb) {
    // stb.ilist.size should be used in preference
    return strbuilder_charAt(stb, stb.ilist.size - 1);
}

void strbuilder_clear(strbuilder_t* stb) {
    __backupText(stb);
    list_clear(&(stb->ilist));
    stb->size = stb->ilist.size;
}

void strbuilder_destroy(strbuilder_t* stb) {
    list_destroy(&(stb->ilist));
    stb->prevTxt = "";
    stb->size = stb->ilist.size;
}

void strbuilder_trim(strbuilder_t* stb) {
    __backupText(stb);
    while(isspace(strbuilder_head(*stb)))
        list_remove(&(stb->ilist), 0);
    while(isspace(strbuilder_tail(*stb)))
        list_remove(&(stb->ilist), stb->ilist.size - 1);
    stb->size = stb->ilist.size;
}

