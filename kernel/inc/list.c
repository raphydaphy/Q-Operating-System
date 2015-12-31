#include "list.h"
#include "strbuilder.h"

list_t list_init() {
    return list_init_s(GROWTH_FACTOR);
}

list_t list_init_s(uint32 ns) {
    list_t rl;
    rl.capt = ns; // You can initialize with 0...
    rl.size = 0;
    rl.autoShrink = false;
    rl.autoShrinkTrigger = GROWTH_FACTOR * 4;
    rl.data = (element_t*) kmalloc(rl.capt * sizeof(element_t));
    return rl;
}

static void __vlist_resize(list_t* lst, uint32 amount) {
    uint32 tempCapt;
    if(amount < lst->size) { //Don't let it resize to less than lst->size
        tempCapt = lst->size;
    } else {
        tempCapt = amount;
    }

    if(tempCapt == lst->capt) return; //There is no need to resize
    lst->capt = tempCapt;
    element_t* oldData = lst->data;
    lst->data = (element_t*) kmalloc(lst->capt * sizeof(element_t));
    memcpy(lst->data, oldData, lst->size * sizeof(element_t));
    kfree(oldData);
}

static inline void __vlist_add(list_t* lst, element_t e, uint32 index) {
    if (index > lst->size) {
        return; // Cannot insert out of the list!
    }
    if (lst->size + 1 >= lst->capt) {
        __vlist_resize(lst, lst->size + GROWTH_FACTOR);
    }
    for (uint32 i = lst->size; i > index; i--) {
        lst->data[i] = lst->data[i - 1];
    }
    lst->data[index] = e;
    lst->size++;
}

inline element_t list_pop(list_t* lst) {
    return list_remove(lst, lst->size);
}

inline void list_adde(list_t* lst, element_t e) {
    __vlist_add(lst, e, lst->size);
}

inline void list_adds(list_t* lst, string e) {
    __vlist_add(lst, makeStrElement(e), lst->size);
}

inline void list_addi(list_t* lst, int e) {
    __vlist_add(lst, makeIntElement(e), lst->size);
}

inline void list_addf(list_t* lst, float e) {
    __vlist_add(lst, makeFloatElement(e), lst->size);
}

inline void list_addc(list_t* lst, char e) {
    __vlist_add(lst, makeCharElement(e), lst->size);
}

inline void list_addAll(list_t* lst, list_t es) {
    for(uint32 iter = 0; iter < es.size; iter++) {
        list_adde(lst, es.data[iter]);
    }
}

inline void list_inserts(list_t* lst, string e, uint32 i) {
    __vlist_add(lst, makeStrElement(e), i);
}

inline void list_inserti(list_t* lst, int e, uint32 i) {
    __vlist_add(lst, makeIntElement(e), i);
}

inline void list_insertf(list_t* lst, float e, uint32 i) {
    __vlist_add(lst, makeFloatElement(e), i);
}

inline void list_insertc(list_t* lst, char e, uint32 i) {
    __vlist_add(lst, makeCharElement(e), i);
}

inline void list_insertAll(list_t* lst, list_t es, uint32 i) {
    for(uint32 iter = 0; iter < es.size; iter++) {
        __vlist_add(lst, es.data[iter], i + iter);
    }
}

inline string list_gets(list_t lst, uint32 index) {
    return etos(lst.data[index]);
}

inline int list_geti(list_t lst, uint32 index) {
    return etoi(lst.data[index]);
}

inline float list_getf(list_t lst, uint32 index) {
    return etof(lst.data[index]);
}

inline char list_getc(list_t lst, uint32 index) {
    return etoc(lst.data[index]);
}

inline etype list_getType(list_t lst, uint32 index) {
    return lst.data[index].ctype;
}

list_t list_sublist(list_t lst, uint32 l, uint32 h) {
    uint32 arrlen = abs(h - l);
    l = l < h ? l : h;
    list_t msg = list_init_s(arrlen);
    for(uint32 i = 0; i < arrlen; i++) {
        __vlist_add(&msg, lst.data[i + l], i);
    }
    return msg;
}

element_t list_remove(list_t* lst, uint32 index) {
    // No need to check for negative (unsigned)
    if (index >= lst->size) {
        return makeNullElement();
    }
    element_t msg = lst->data[index];
    for (uint32 i = index; i < lst->size - 1; i++) {
        lst->data[i] = lst->data[i + 1];
    }
    lst->data[lst->size] = makeNullElement();
    lst->size--;
    if (lst->autoShrink) {
        if (lst->capt - lst->size >= lst->autoShrinkTrigger) {
            __vlist_resize(lst, lst->size + GROWTH_FACTOR);
        }
    }
    return msg;
}

static element_t __vlist_replace(list_t* lst, uint32 index, element_t e) {
    if (index >= lst->size) {
        return makeNullElement();
    }
    element_t msg = lst->data[index];
    lst->data[index] = e;
    return msg;
}

inline element_t list_replaces(list_t* lst, uint32 index, string e) {
    return __vlist_replace(lst, index, makeStrElement(e));
}

inline element_t list_replacei(list_t* lst, uint32 index, int e) {
    return __vlist_replace(lst, index, makeIntElement(e));
}

inline element_t list_replacef(list_t* lst, uint32 index, float e) {
    return __vlist_replace(lst, index, makeFloatElement(e));
}

inline element_t list_replacec(list_t* lst, uint32 index, char e) {
    return __vlist_replace(lst, index, makeCharElement(e));
}

inline void list_shrink(list_t* lst) {
    __vlist_resize(lst, lst->size);
}

void list_clear(list_t* lst) {
    kfree(lst->data);
    lst->capt = GROWTH_FACTOR;
    lst->size = 0;
    lst->data = (element_t*) kmalloc(lst->capt * sizeof(element_t));
}

uint32 list_indexOf(list_t* lst, element_t e) {
    for(uint32 i = 0; i < lst->size; i++) {
        if (eqlElement_t(lst->data[i], e)) {
            return i;
        }
    }
    return lst->size; // This is a OutOfBounds
}

inline bool list_contains(list_t* lst, element_t e) {
    return list_indexOf(lst, e) < (lst->size);
}

void list_flip(list_t* lst) {
    uint32 len = lst->size;
    uint32 spi = (uint32) (lst->size / 2);
    element_t tmp;
    for (uint32 i = 0; i < spi; i++) {
        tmp = __vlist_replace(lst, i, lst->data[--len]);
        __vlist_replace(lst, len, tmp);
    }
}

void list_destroy(list_t* lst) {
    kfree(lst->data);
    lst->capt = lst->size = 0;
}

string list_toString(list_t lst)
{
    strbuilder_t sb = strbuilder_init();
    strbuilder_append(&sb, "[");
    strbuilder_append(&sb, element_toString(lst.data[0]));
    for(uint16 i = 1; i < lst.size; i++)
    {
        strbuilder_append(&sb, ", ");
        strbuilder_append(&sb, element_toString(lst.data[i]));
    }
    strbuilder_append(&sb, "]");
    string msg = strbuilder_tostr(sb);
    strbuilder_destroy(&sb);
    return msg;
}

