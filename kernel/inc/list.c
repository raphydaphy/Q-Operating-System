#include "list.h"

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

static void __vlist_add(list_t* lst, element_t e) {
    if (lst->size == lst->capt) list_resize(lst, lst->size + GROWTH_FACTOR);
    lst->data[lst->size] = e;
    lst->size++;
}

void list_adds(list_t* lst, string e) {
     element_t tmp = makeNullElement();
     tmp.strdata = e;
     __vlist_add(lst, tmp);
}

void list_addi(list_t* lst, int e) {
     element_t tmp = makeNullElement();
     tmp.intdata = e;
     __vlist_add(lst, tmp);
}

void list_addf(list_t* lst, float e) {
     element_t tmp = makeNullElement();
     tmp.floatdata = e;
     __vlist_add(lst, tmp);
}

void list_addc(list_t* lst, char e) {
     element_t tmp = makeNullElement();
     tmp.chardata = e;
     __vlist_add(lst, tmp);
}

string list_gets(list_t lst, uint32 index) {
    return lst.data[index].strdata;
}

int list_geti(list_t lst, uint32 index) {
    return lst.data[index].intdata;
}

float list_getf(list_t lst, uint32 index) {
    return lst.data[index].floatdata;
}

char list_getc(list_t lst, uint32 index) {
    return lst.data[index].chardata;
}

element_t list_remove(list_t* lst, uint32 index) {
    // No need to check for negative (unsigned)
    if (index >= lst->size) return makeNullElement();
    element_t msg = lst->data[index];
    for (uint32 i = index; i < lst->size-1; i++) {
        lst->data[i] = lst->data[i+1];
    }
    lst->data[lst->size] = makeNullElement();
    lst->size--;
    if (lst->autoShrink)
        if (lst->capt - lst->size >= lst->autoShrinkTrigger)
            list_resize(lst, lst->size + GROWTH_FACTOR);
    return msg;
}

static element_t __vlist_replace(list_t* lst, uint32 index, element_t e) {
    if (index >= lst->size) return makeNullElement();
    element_t msg = lst->data[index];
    lst->data[index] = e;
    return msg;
}

element_t list_replaces(list_t* lst, uint32 index, string e) {
    element_t ne = makeNullElement();
    ne.strdata = e;
    return __vlist_replace(lst, index, ne);
}

element_t list_replacei(list_t* lst, uint32 index, int e) {
    element_t ne = makeNullElement();
    ne.intdata = e;
    return __vlist_replace(lst, index, ne);
}

element_t list_replacef(list_t* lst, uint32 index, float e) {
    element_t ne = makeNullElement();
    ne.floatdata = e;
    return __vlist_replace(lst, index, ne);
}

element_t list_replacec(list_t* lst, uint32 index, char e) {
    element_t ne = makeNullElement();
    ne.chardata = e;
    return __vlist_replace(lst, index, ne);
}

void list_shrink(list_t* lst) {
    list_resize(lst, lst->size);
}

void list_resize(list_t* lst, uint32 amount) {
    uint32 tempCapt;
    if(amount < lst->size) //Don't let it resize to less than lst->size
        tempCapt = lst->size;
    else tempCapt = amount;

    if(tempCapt == lst->capt) return; //There is no need to resize
    lst->capt = tempCapt;
    element_t* oldData = lst->data;
    lst->data = (element_t*) kmalloc(lst->capt * sizeof(element_t));
    memcpy(lst->data, oldData, lst->size * sizeof(element_t));
    kfree(oldData);
}

void list_clear(list_t* lst) {
    kfree(lst->data);
    lst->capt = GROWTH_FACTOR;
    lst->size = 0;
    lst->data = (element_t*) kmalloc(lst->capt * sizeof(element_t));
}

uint32 list_indexOf(list_t* lst, element_t e) {
    for(uint32 i = 0; i < lst->size; i++) {
        if (cmpElement_t(lst->data[i], e)) {
            return i;
        }
    }
    return lst->size; // This is a OutOfBounds
}

bool list_contains(list_t* lst, element_t e) {
    return list_indexOf(lst, e) < (lst->size);
}

void list_destroy(list_t* lst) {
    kfree(lst->data);
    lst->capt = lst->size = 0;
}
