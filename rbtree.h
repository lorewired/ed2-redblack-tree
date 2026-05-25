#ifndef RBTREE_H
#define RBTREE_H

#include "utils.h"

#define RED 1
#define BLACK 0

#define LEFT 1
#define RIGHT 0

#pragma region RB_TREE_NODE
typedef struct _rbtree_node {
    struct _rbtree_node* left;
    struct _rbtree_node* right;
    void*                value;
    char                 colour;
} rbtree_node;

rbtree_node* new_rbtree_node(void* value);

void rbtree_switch_colour(rbtree_node* node);
#pragma endregion

#pragma region RB_TREE
typedef struct {
    int32_t (* cmp) (void* u, void* v);
    rbtree_node* root;
    uint32_t     size;
} rbtree;

rbtree new_rbtree();

void rbtree_insert(rbtree* tree, void* value);

void rbtree_erase(rbtree* tree, void* value);

uint32_t rbtree_size(rbtree* tree);

bool rbtree_empty(rbtree* tree);

bool rbtree_direction(rbtree* tree, rbtree_node* left, rbtree_node* right);
#pragma endregion

#endif