#ifndef RBTREE_H
#define RBTREE_H

#include "utils.h"
#include "stack.h"

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

bool rbtree_is_black(rbtree_node* node);

bool rbtree_is_red(rbtree_node* node);

bool rbtree_has_same_colour(rbtree_node* u, rbtree_node* v);
#pragma endregion

#pragma region RB_TREE
typedef struct {
    int32_t (* cmp) (void* u, void* v);
    rbtree_node* root;
    uint32_t     size;
} rbtree;

rbtree new_rbtree(int32_t (* cmp) (void* x, void* y));

void rbtree_insert_impl(rbtree* tree, void* value);

#define rbtree_insert(tree, val)                          \
do {                                                      \
    __typeof__(val) *tmp = malloc(sizeof(val));           \
    *tmp = (val);                                         \
    rbtree_insert_impl((tree), tmp);                      \
} while (0)

void rbtree_erase(rbtree* tree, void* value);

uint32_t rbtree_size(rbtree* tree);

bool rbtree_empty(rbtree* tree);

bool rbtree_direction(rbtree* tree, void* node_value, void* value);

void* rbtree_ll_rotation(rbtree_node* cur, rbtree_node* par, rbtree_node* grand, rbtree_node* unc);

void* rbtree_rr_rotation(rbtree_node* cur, rbtree_node* par, rbtree_node* grand, rbtree_node* unc);

void* rbtree_lr_rotation(rbtree_node* cur, rbtree_node* par, rbtree_node* grand, rbtree_node* unc);

void* rbtree_rl_rotation(rbtree_node* cur, rbtree_node* par, rbtree_node* grand, rbtree_node* unc);

rbtree_node* rbtree_rotate(rbtree_node* cur, rbtree_node* par, rbtree_node* grand);

void debug(rbtree* tree);
#pragma endregion

#endif