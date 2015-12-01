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

