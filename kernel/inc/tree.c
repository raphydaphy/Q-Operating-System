#include "tree.h"

node_t node_init(element_t element, node_t *leftn, node_t *rightn)
{
    node_t node;
    node.data = element;
    node.left = leftn;
    node.right = rightn;
    return node;
}

node_t leafless_node_init(element_t element)
{
    node_t node;
    node.data = element;
    node.left = NULL;
    node.right = NULL;
    return node;
}

tree_t tree_init(node_t *rootNode)
{
    tree_t tree;
    tree.node = rootNode;
    return tree;
}

static inline list_t __tree_fold_preorder(node_t *tree)
{
    list_t list = list_init();
    list_adde(&list, tree->data);
    if(tree->left != NULL)
    {
        list_t leftList = __tree_fold_preorder(tree->left);
        list_addAll(&list, leftList);
        list_destroy(&leftList);
    }
    if(tree->right != NULL)
    {
        list_t rightList = __tree_fold_preorder(tree->right);
        list_addAll(&list, rightList);
        list_destroy(&rightList);
    }
    return list;
}

static inline list_t __tree_fold_inorder(node_t *tree)
{
    list_t list = list_init();
    if(tree->left != NULL)
    {
        list_t leftList = __tree_fold_inorder(tree->left);
        list_addAll(&list, leftList);
        list_destroy(&leftList);
    }
    list_adde(&list, tree->data);
    if(tree->right != NULL)
    {
        list_t rightList = __tree_fold_inorder(tree->right);
        list_addAll(&list, rightList);
        list_destroy(&rightList);
    }
    return list;
}

static inline list_t __tree_fold_postorder(node_t *tree)
{
    list_t list = list_init();
    if(tree->left != NULL)
    {
        list_t leftList = __tree_fold_postorder(tree->left);
        list_addAll(&list, leftList);
        list_destroy(&leftList);
    }
    if(tree->right != NULL)
    {
        list_t rightList = __tree_fold_postorder(tree->right);
        list_addAll(&list, rightList);
        list_destroy(&rightList);
    }
    list_adde(&list, tree->data);
    return list;
}

list_t tree_foldOrder(tree_t tree, tree_order order)
{
    switch(order)
    {
    case PRE_ORDER:
        return __tree_fold_preorder(tree.node);
    case IN_ORDER:
        return __tree_fold_inorder(tree.node);
    case POST_ORDER:
        return __tree_fold_postorder(tree.node);
    default:
        return list_init();
    }
}

static inline uint32 __tree_count_node(node_t *node)
{
    uint32 nodeCount = 1;
    // No need != NULL since NULL is the same as false
    nodeCount += node->left ? __tree_count_node(node->left) : 0;
    nodeCount += node->right ? __tree_count_node(node->right) : 0;
    return nodeCount;
}

uint32 tree_countNodes(tree_t tree)
{
    return __tree_count_node(tree.node);
}

