#ifndef TREE_H
#define TREE_H

#include "dynsto.h"
#include "list.h"

typedef struct node_t {
    element_t data;
    struct node_t *left;
    struct node_t *right;
} node_t;

typedef struct {
    node_t *node;
} tree_t;

typedef enum {
    PRE_ORDER,  // data, left, right
    IN_ORDER,   // left, data, right
    POST_ORDER  // left, right, data
} tree_order;

node_t node_init(element_t, node_t*, node_t*);

node_t leafless_node_init(element_t);

tree_t tree_init(node_t*);

list_t tree_foldOrder(tree_t, tree_order);

#endif
