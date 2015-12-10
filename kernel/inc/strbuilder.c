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
    stb->size++;
}

void strbuilder_appends(strbuilder_t* stb, string str) {
    __backupText(stb);
    do {
        list_addc(&(stb->ilist), *str++);
    } while (*str != 0);
    stb->size = stb->ilist.size;
}

void strbuilder_inserts(strbuilder_t* stb, string str, uint32 index) {
    __backupText(stb);
    do {
        list_insertc(&(stb->ilist), *str++, index++);
    } while (*str != 0);
    stb->size = stb->ilist.size;
}

void strbuilder_insertc(strbuilder_t* stb, char c, uint32 index) {
    __backupText(stb);
    stb->size++;
    list_insertc(&(stb->ilist), c, index);
}

void strbuilder_flip(strbuilder_t* stb) {
    __backupText(stb);
    list_flip(&(stb->ilist));
}

void strbuilder_replaces(strbuilder_t* stb, string str, uint32 l) {
    __backupText(stb);
    do {
        list_replacec(&(stb->ilist), *str++, l++);
    } while (*str != 0);
}

void strbuilder_replacec(strbuilder_t* stb, char c, uint32 l) {
    __backupText(stb);
    list_replacec(&(stb->ilist), c, l);
}

static inline string __vstb_tos(strbuilder_t stb, uint32 l, uint32 h) {
    uint32 strlen = abs(h - l);
    if (strlen > stb.ilist.size) {
        return ""; // Do not return NULL!
    }
    string msg = (string) kmalloc((strlen) * sizeof(char));
    l = l < h ? l : h; // Make sure l is actually smaller than h
    uint32 i = 0;
    for( ; i < strlen; i++) {
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

char strbuilder_head(strbuilder_t stb) {
    return strbuilder_charAt(stb, 0);
}

char strbuilder_tail(strbuilder_t stb) {
    // Use stb.ilist.size because it is more accurate
    return strbuilder_charAt(stb, stb.ilist.size - 1);
}

char strbuilder_charAt(strbuilder_t stb, uint32 i) {
    return list_getc(stb.ilist, i);
}

// "!ABC!" -> (_, 1, 1) := "ABC" ret Void
void strbuilder_rmOuter(strbuilder_t* stb, uint32 l, uint32 h) {
    __backupText(stb);
    if(l < h) {
        swapui(&l, &h);
    }
    uint32 i = 0;
    for( ; i < l; i++) {
        list_remove(&(stb->ilist), i);
    }
    for(i = 0; i < h; i++) {
        list_remove(&(stb->ilist), stb->ilist.size - 1);
    }
    stb->size = stb->ilist.size;
}

char strbuilder_rmchar(strbuilder_t* stb, uint32 l) {
    __backupText(stb);
    stb->size--;
    return etoc(list_remove(&(stb->ilist), l));
}

string strbuilder_delete(strbuilder_t* stb, uint32 l, uint32 h) {
    __backupText(stb);
    uint32 dist = abs(h - l);
    string msg = (string) kmalloc(dist * sizeof(char));
    l = l < h ? l : h; // Make sure l is actually smaller than h
    uint32 i = 0;
    for( ; i < dist; i++) {
        msg[i] = etoc(list_remove(&(stb->ilist), l));
    }
    stb->size = stb->ilist.size;
    msg[i] = '\0';
    return msg;
}

string strbuilder_clear(strbuilder_t* stb) {
    __backupText(stb);
    list_clear(&(stb->ilist));
    return stb->prevTxt;
}

void strbuilder_destroy(strbuilder_t* stb) {
    list_destroy(&(stb->ilist));
    stb->prevTxt = "";
}

inline bool strbuilder_contains(strbuilder_t stb, string str) {
    return strbuilder_indexOf(stb, str) < stb.size;
}

static inline uint32 __strb_indexOf(strbuilder_t stb, string str, uint32 sindex) {
    if (sindex >= stb.size) {
        return stb.size; // Obviously cannot find outside of str
    }
    uint32 tstrlen = strlen(str);
    for(uint32 i = sindex; (i + tstrlen) < stb.size; i++) {
        string test = strbuilder_substr(stb, i, i + tstrlen);
        if (streql(str, test)) {
            return i;
        }
    }
    return stb.size;
}

inline uint32 strbuilder_indexOf(strbuilder_t stb, string str) {
    return __strb_indexOf(stb, str, 0);
}

inline uint32 strbuilder_indexFrom(strbuilder_t stb, string str, uint32 sindex) {
    return __strb_indexOf(stb, str, sindex);
}

void strbuilder_trim(strbuilder_t* stb) {
    __backupText(stb);
    while(isspace(strbuilder_head(*stb))) {
        strbuilder_delete(stb, 0, 1);
    }
    while(isspace(strbuilder_tail(*stb))) {
        strbuilder_delete(stb, stb->ilist.size - 1, stb->ilist.size);
    }
    stb->size = stb->ilist.size;
}

