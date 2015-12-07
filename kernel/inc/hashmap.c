#include "hashmap.h"

static const uint32 __shrinkTrigger = GROWTH_FACTOR * 4;

hashmap_t hashmap_init() {
    hashmap_t rl;
    rl.capt = GROWTH_FACTOR;
    rl.size = 0;
    rl.data = (tuple_t*) kmalloc(rl.capt * sizeof(tuple_t));
    return rl;
}

static void __set_resize(hashmap_t* set, uint32 amount) {
    uint32 tempCapt;
    if(amount < set->size) { //Don't let it resize to less than lst->size
        tempCapt = set->size;
    } else {
        tempCapt = amount;
    }
    if(tempCapt == set->capt) {
        return; //There is no need to resize
    }
    set->capt = tempCapt;
    tuple_t* oldData = set->data;
    set->data = (tuple_t*) kmalloc(set->capt * sizeof(tuple_t));
    memcpy(set->data, oldData, set->size * sizeof(tuple_t));
    kfree(oldData);
}

static uint32 __vhashmap_indexOf(hashmap_t rl, string k) {
    for(uint32 i = 0; i < rl.size; i++) {
        if(streql(k, rl.data[i].key)) {
            return i;
        }
    }
    return rl.size;
}

void hashmap_add(hashmap_t* rl, string s, element_t e) {
    uint32 pos = __vhashmap_indexOf(*rl, s);
    if(pos < rl->size) {
        rl->data[pos].val = e;
    } else {
        if (rl->size == rl->capt) {
            __set_resize(rl, rl->size + GROWTH_FACTOR);
        }
        rl->data[rl->size] = tuple_init(s, e);
        rl->size++;
    }
}

inline bool hashmap_hasKey(hashmap_t rl, string k) {
    return __vhashmap_indexOf(rl, k) < rl.size;
}

element_t hashmap_getVal(hashmap_t rl, string k) {
    uint32 pos = __vhashmap_indexOf(rl, k);
    if(pos < rl.size) {
        return rl.data[pos].val;
    }
    return makeNullElement();
}

void hashmap_destroy(hashmap_t* map) {
    kfree(map->data);
    map->size = map->capt = 0;
}

tuple_t tuple_init(string k, element_t v) {
    tuple_t msg;
    msg.key = k;
    msg.val = v;
    return msg;
}

