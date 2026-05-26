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
rbtree new_rbtree(int32_t (* cmp) (void* u, void* v)) {
    return (rbtree) {
        .cmp  = cmp,
        .root = NULL,
        .size = 0
    };
}

bool rbtree_direction(rbtree* tree, void* node_value, void* value) {
    return tree->cmp(node_value, value) <= 0 ? LEFT : RIGHT;
}

void rbtree_insert(rbtree* tree, void* value) {
    if (!tree->root) {
        tree->root = new_rbtree_node(value);
        rbtree_switch_colour(tree->root);
        tree->size++;
        return;
    }
    stack stk = new_stack();
    rbtree_node* new_node = NULL;
    rbtree_node* grand = NULL;
    rbtree_node* par   = NULL;
    rbtree_node* cur   = tree->root;
    while (true) {
        stack_push(&stk, cur);
        grand = par;
        par   = cur;
        bool dir = rbtree_direction(tree, cur->value, value);
        if (dir == LEFT) {
            if (!cur->left) {
                new_node = cur->left = new_rbtree_node(value);
                break;
            }
            cur = cur->left;
        } else {
            if (!cur->right) {
                new_node = cur->right = new_rbtree_node(value);
                break;
            }
            cur = cur->right;
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