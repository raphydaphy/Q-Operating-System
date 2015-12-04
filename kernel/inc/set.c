#include "set.h"

static const int __shrinkTrigger = GROWTH_FACTOR * 4;

set_t set_init() {
    set_t rl;
    rl.capt = GROWTH_FACTOR;
    rl.size = 0;
    rl.data = (element_t*) kmalloc(rl.capt * sizeof(element_t));
    return rl;
}

static void __set_resize(set_t* set, uint32 amount) {
    uint32 tempCapt;
    if(amount < set->size) //Don't let it resize to less than lst->size
        tempCapt = set->size;
    else tempCapt = amount;

    if(tempCapt == set->capt) return; //There is no need to resize
    set->capt = tempCapt;
    element_t* oldData = set->data;
    set->data = (element_t*) kmalloc(set->capt * sizeof(element_t));
    memcpy(set->data, oldData, set->size * sizeof(element_t));
    kfree(oldData);
}

static void __vset_add(set_t* set, element_t e) {
    if (set_contains(set, e)) return;
    if (set->size == set->capt) __set_resize(set, set->size + GROWTH_FACTOR);
    set->data[set->size] = e;
    set->size++;
}

void set_adds(set_t* set, string e) {
    element_t tmp = makeNullElement();
    tmp.strdata = e;
    __vset_add(set, tmp);
}

void set_addi(set_t* set, int e) {
    element_t tmp = makeNullElement();
    tmp.intdata = e;
    __vset_add(set, tmp);
}

void set_addf(set_t* set, float e) {
    element_t tmp = makeNullElement();
    tmp.floatdata = e;
    __vset_add(set, tmp);
}

void set_addc(set_t* set, char e) {
    element_t tmp = makeNullElement();
    tmp.chardata = e;
    __vset_add(set, tmp);
}

uint32 set_indexOf(set_t* lst, element_t e) {
    for(uint32 i = 0; i < lst->size; i++) {
        if (cmpElement_t(lst->data[i], e)) {
            return i;
        }
    }
    return lst->size; // This is a OutOfBounds
}

bool set_contains(set_t* lst, element_t e) {
    return set_indexOf(lst, e) < (lst->size);
}

void set_destroy(set_t* lst) {
    kfree(lst->data);
    lst->capt = lst->size = 0;
}

string set_gets(set_t lst, uint32 index) {
    return lst.data[index].strdata;
}

int set_geti(set_t lst, uint32 index) {
    return lst.data[index].intdata;
}

float set_getf(set_t lst, uint32 index) {
    return lst.data[index].floatdata;
}

char set_getc(set_t lst, uint32 index) {
    return lst.data[index].chardata;
}

void set_union(set_t* a, set_t* b) {
    for(uint32 i = 0; i < b->size; i++)
        __vset_add(a, b->data[i]);
}

void set_intersect(set_t* a, set_t* b) {
    set_t tmp = set_init();
    for(uint32 i = 0; i < b->size; i++)
        if(set_contains(a, b->data[i]))
            __vset_add(&tmp, b->data[i]);
    *a = tmp;
}

