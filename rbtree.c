#include "rbtree.h"

#pragma region RBTREE_NODE
rbtree_node* new_rbtree_node(void* value) {
    rbtree_node* node = malloc(sizeof(rbtree_node));
    if (node) {
        node->left   = node->right = NULL;
        node->value  = value;
        node->colour = RED;
    }
    return node;
}

void rbtree_switch_colour(rbtree_node* node) {
    if (!node) return;
    node->colour ^= RED;
}
#pragma endregion

#pragma region RBTREE
rbtree new_rbtree() {
    return (rbtree) {
        .root = NULL,
        .size = 0
    };
}

bool rbtree_direction(rbtree* tree, rbtree_node* left, rbtree_node* right, void* value) {
}

void rbtree_insert(rbtree* tree, void* value) {
    if (!tree->root) {
        tree->root = new_rbtree_node(value);
        rbtree_switch_colour(tree->root);
        tree->size++;
        return;
    }
    rbtree_node* grand = NULL;
    rbtree_node* par   = NULL;
    rbtree_node* cur   = tree->root;
    while (true) {
        bool dir = rbtree_direction(tree, cur->left, cur->right, value);
        if (dir == LEFT) {
            
        }
    }
}

void rbtree_erase(rbtree* tree, void* value) {
    // TODO
}

uint32_t rbtree_size(rbtree* tree) {
    return tree->size;
}

bool rbtree_empty(rbtree* tree) {
    return ! tree->size;
}
#pragma endregion