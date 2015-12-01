#include "list.h"

list_t init_list() {
    list_t rl;
    rl.capt = GROWTH_FACTOR;
    rl.size = 0;
    rl.data = kmalloc(rl.capt * sizeof(string));
    return rl;
}

void add(list_t* lst, string e) {
    if (lst->size == lst->capt) {
        lst->capt += GROWTH_FACTOR;
        string* oldData = lst->data;
        uint32 len = lst->capt * sizeof(string);
        lst->data = kmalloc(len);
        memcpy(lst->data, oldData, len);
    }
    lst->data[lst->size] = e;
    lst->size++;
}

void remove(list_t* lst) {
    lst->data[lst->size] = NULL;
    lst->size--;
}

void shrink(list_t* lst) {
    lst->capt = lst->size;
    string* oldData = lst->data;
    uint32 len = lst->capt * sizeof(string);
    lst->data = kmalloc(len);
    memcpy(lst->data, oldData, len);
}

void clear(list_t* lst) {
    kfree(lst->data);
    lst->capt = GROWTH_FACTOR;
    lst->size = 0;
    lst->data = kmalloc(lst->capt * sizeof(string));
}

uint32 indexOf(list_t* lst, string e) {
    for(uint32 i = 0; i < lst->size; i++) {
        if (strEql(lst->data[i], e)) {
            return i;
        }
    }
    return lst->size; // This is a OutOfBounds
}

bool contains(list_t* lst, string e) {
    return indexOf(lst, e) < (lst->size);
}
