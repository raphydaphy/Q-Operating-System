#ifndef HASHMAP_H
#define HASHMAP_H

#include "dynsto.h"

typedef struct {
    // Cmp hash first. If hash eq, then check key
    // if hash ne, key must be diff
    int hash;
    string key;
    element_t val;
} tuple_t;

typedef struct {
    tuple_t* data;
    uint32 capt;
    uint32 size;
} hashmap_t;

typedef hashmap_t map_t;

hashmap_t hashmap_init();

tuple_t tuple_init(string, element_t);

tuple_t tuple_initNull();

void hashmap_add(hashmap_t*, string, element_t);

void hashmap_merge(hashmap_t*, hashmap_t);

element_t hashmap_rmFirst(hashmap_t*, string);

element_t* hashmap_rmAll(hashmap_t*, string);

bool hashmap_hasKey(hashmap_t, string);

element_t hashmap_getVal(hashmap_t, string);

void hashmap_destroy(hashmap_t*);

#endif
