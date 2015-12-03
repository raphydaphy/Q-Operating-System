#include "list.h"

list_t list_init() {
    list_t rl;
    rl.capt = GROWTH_FACTOR;
    rl.size = 0;
    rl.autoShrink = false;
    rl.autoShrinkTrigger = GROWTH_FACTOR * 4;
    rl.data = (pdata_t*) kmalloc(rl.capt * sizeof(pdata_t));
    return rl;
}

list_t list_init_s(uint32 ns) {
    list_t rl;
    rl.capt = ns; // You can initialize with 0...
    rl.size = 0;
    rl.autoShrink = false;
    rl.autoShrinkTrigger = GROWTH_FACTOR * 4;
    rl.data = (pdata_t*) kmalloc(rl.capt * sizeof(pdata_t));
    return rl;
}

static pdata_t __makeNull() {
    pdata_t tmp;
    tmp.intdata = NULL;
    return tmp;
}

static void __vlist_add(list_t* lst, pdata_t e) {
    if (lst->size == lst->capt) list_resize(lst, lst->size + GROWTH_FACTOR);
    lst->data[lst->size] = e;
    lst->size++;
}

void list_adds(list_t* lst, string e) {
     pdata_t tmp = __makeNull();
     tmp.strdata = e;
     __vlist_add(lst, tmp);
}

void list_addi(list_t* lst, int e) {
     pdata_t tmp = __makeNull();
     tmp.intdata = e;
     __vlist_add(lst, tmp);
}

void list_addf(list_t* lst, float e) {
     pdata_t tmp = __makeNull();
     tmp.floatdata = e;
     __vlist_add(lst, tmp);
}

void list_addc(list_t* lst, char e) {
     pdata_t tmp = __makeNull();
     tmp.floatdata = e;
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

string list_heads(list_t lst) {
    return list_gets(lst, 0);
}

int list_headi(list_t lst) {
    return list_geti(lst, 0);
}

float list_headf(list_t lst) {
    return list_getf(lst, 0);
}

char list_headc(list_t lst) {
    return list_getc(lst, 0);
}

pdata_t list_remove(list_t* lst, uint32 index) {
    // No need to check for negative (unsigned)
    if (index >= lst->size) return __makeNull();
    pdata_t msg = lst->data[index];
    for (uint32 i = index; i < lst->size-1; i++) {
        lst->data[i] = lst->data[i+1];
    }
    lst->data[lst->size] = __makeNull();
    lst->size--;
    if (lst->autoShrink)
        if (lst->capt - lst->size >= lst->autoShrinkTrigger)
            list_resize(lst, lst->size + GROWTH_FACTOR);
    return msg;
}

static pdata_t __vlist_replace(list_t* lst, uint32 index, pdata_t e) {
    if (index >= lst->size) return __makeNull();
    pdata_t msg = lst->data[index];
    lst->data[index] = e;
    return msg;
}

pdata_t list_replaces(list_t* lst, uint32 index, string e) {
    pdata_t ne = __makeNull();
    ne.strdata = e;
    return __vlist_replace(lst, index, ne);
}

pdata_t list_replacei(list_t* lst, uint32 index, int e) {
    pdata_t ne = __makeNull();
    ne.intdata = e;
    return __vlist_replace(lst, index, ne);
}

pdata_t list_replacef(list_t* lst, uint32 index, float e) {
    pdata_t ne = __makeNull();
    ne.floatdata = e;
    return __vlist_replace(lst, index, ne);
}

pdata_t list_replacec(list_t* lst, uint32 index, char e) {
    pdata_t ne = __makeNull();
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
    pdata_t* oldData = lst->data;
    lst->data = (pdata_t*) kmalloc(lst->capt * sizeof(pdata_t));
    memcpy(lst->data, oldData, lst->size * sizeof(pdata_t));
    kfree(oldData);
}

void list_clear(list_t* lst) {
    kfree(lst->data);
    lst->capt = GROWTH_FACTOR;
    lst->size = 0;
    lst->data = (pdata_t*) kmalloc(lst->capt * sizeof(pdata_t));
}

static bool __cmpPdata_t(pdata_t a, pdata_t b) {
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

uint32 list_indexOf(list_t* lst, pdata_t e) {
    for(uint32 i = 0; i < lst->size; i++) {
        if (__cmpPdata_t(lst->data[i], e)) {
            return i;
        }
    }
    return lst->size; // This is a OutOfBounds
}

bool list_contains(list_t* lst, pdata_t e) {
    return list_indexOf(lst, e) < (lst->size);
}

void list_destroy(list_t* lst) {
    kfree(lst->data);
    lst->capt = lst->size = 0;
}
