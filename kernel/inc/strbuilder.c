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

static string __vstb_tos(strbuilder_t stb, uint32 l, uint32 h) {
    uint32 strlen = abs(h - l);
    if (strlen > stb.ilist.size) return NULL;
    string msg = (string) kmalloc((strlen) * sizeof(char));
    l = l < h ? l : h; // Make sure l is actually smaller than h
    uint32 i = 0;
    for(i = 0; i < strlen; i++) {
        msg[i] = list_getc(stb.ilist, i + l);
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

inline char strbuilder_head(strbuilder_t stb) {
    return strbuilder_charAt(stb, 0);
}

inline char strbuilder_tail(strbuilder_t stb) {
    return strbuilder_charAt(stb, stb.ilist.size);
}

inline char strbuilder_charAt(strbuilder_t stb, uint32 i) {
    return list_getc(stb.ilist, i);
}

void strbuilder_delete(strbuilder_t* stb, uint32 l, uint32 h) {
    __backupText(stb);
    uint32 dist = abs(h - l);
    while(dist-- > 0) {
        list_remove(&(stb->ilist), l);
    }
}

void strbuilder_clear(strbuilder_t* stb) {
    __backupText(stb);
    list_clear(&(stb->ilist));
}

void strbuilder_destroy(strbuilder_t* stb) {
    list_destroy(&(stb->ilist));
    stb->prevTxt = "";
}

uint32 strbuilder_indexOf(strbuilder_t stb, string str) {
    uint32 tstrlen = strlen(str);
    for(uint32 i = 0; (i + tstrlen) < stb.size; i++) {
        if (streql(str, strbuilder_substr(stb, i, i + tstrlen))) return i;
    }
    return stb.size;
}

void strbuilder_trim(strbuilder_t* stb) {
    __backupText(stb);
    while(isspace(strbuilder_head(*stb)))
        strbuilder_delete(stb, 0, 1);
    while(isspace(strbuilder_tail(*stb)))
        strbuilder_delete(stb, stb->ilist.size - 1, stb->ilist.size);
    stb->size = stb->ilist.size;
}
