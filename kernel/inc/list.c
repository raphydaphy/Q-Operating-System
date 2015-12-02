#include "list.h"

list_t list_init() {
    list_t rl;
    rl.capt = GROWTH_FACTOR;
    rl.size = 0;
    rl.autoShrink = false;
    rl.autoShrinkTrigger = GROWTH_FACTOR*4;
    rl.data = (string*) kmalloc(rl.capt * sizeof(string));
    return rl;
}

list_t list_init_s(uint32 ns) {
    list_t rl;
    rl.capt = ns; // You can initialize with 0...
    rl.size = 0;
    rl.autoShrink = false;
    rl.autoShrinkTrigger = GROWTH_FACTOR*4;
    rl.data = (string*) kmalloc(rl.capt * sizeof(string));
    return rl;
}

void list_add(list_t* lst, string e) {
    if (lst->size == lst->capt) {
        list_resize(lst, lst->size + GROWTH_FACTOR);
    }
    lst->data[lst->size] = e;
    lst->size++;
}

void list_remove(list_t* lst, uint32 index) {
    // No need to check for negative (unsigned)
    if (index >= lst->size) return;
    for (uint8 i = index; i < lst->size-1; i++){
        lst->data[i] = lst->data[i+1];
    }
    lst->data[index] = NULL;
    lst->size--;
    if (lst->autoShrink)
        if (lst->capt - lst->size >= lst->autoShrinkTrigger)
            list_resize(lst, lst->size + GROWTH_FACTOR);
}

void list_pop(list_t* lst) {
    lst->data[lst->size] = NULL;
    lst->size--;
    if (lst->autoShrink)
        if (lst->capt - lst->size >= lst->autoShrinkTrigger)
            list_resize(lst, lst->size + GROWTH_FACTOR);
}

void list_shift(list_t* lst) {
    for (uint8 i = 0; i < lst->size-1; i++){
        lst->data[i] = lst->data[i+1];
    }
    lst->data[0] = NULL;
    lst->size--;
    if (lst->autoShrink)
        if (lst->capt - lst->size >= lst->autoShrinkTrigger)
            list_resize(lst, lst->size + GROWTH_FACTOR);
}

void list_replace(list_t* lst, uint32 index, string e) {
    if (index >= lst->size) return;
    lst->data[index] = e;
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
    string* oldData = lst->data;
    lst->data = (string*) kmalloc(lst->capt * sizeof(string));
    memcpy(lst->data, oldData, lst->size * sizeof(string));
    kfree(oldData);
}

void list_clear(list_t* lst) {
    kfree(lst->data);
    lst->capt = GROWTH_FACTOR;
    lst->size = 0;
    lst->data = (string*) kmalloc(lst->capt * sizeof(string));
}

uint32 list_indexOf(list_t* lst, string e) {
    for(uint32 i = 0; i < lst->size; i++)
        if (strEql(lst->data[i], e))
            return i;
    return lst->size; // This is a OutOfBounds
}

bool list_contains(list_t* lst, string e) {
    return list_indexOf(lst, e) < (lst->size);
}

void list_destroy(list_t* lst) {
    kfree(lst->data);
    lst->capt = lst->size = 0;
}
