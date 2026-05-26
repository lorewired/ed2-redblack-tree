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

bool rbtree_is_black(rbtree_node* node) {
    return !node || node->colour == BLACK;
}

bool rbtree_is_red(rbtree_node* node) {
    return node && node->colour == RED;
}

bool rbtree_has_same_colour(rbtree_node* u, rbtree_node* v) {
    return u->colour == v->colour;
}
#pragma endregion

#pragma region RBTREE
void debug(rbtree* tree) {
    stack stk = new_stack();
    stack_push(&stk, tree->root);
    printf("SIZE: %u\n", tree->size);
    printf("DEBUG\n");
    printf("%d ROOT COLOUR: %s\n", to_int32(tree->root->value), (tree->root->colour == RED ? "RED" : "BLACK"));
    while (stack_size(&stk)) {
        rbtree_node* cur = stack_pop(&stk);
        printf("%d %s: ", to_int32(cur->value), (cur->colour == RED ? "RED" : "BLACK"));
        if (cur->left) {
            printf("(LEFT: %d %s) ", to_int32(cur->left->value), (cur->left->colour == RED ? "RED" : "BLACK"));
            stack_push(&stk, cur->left);
        }
        if (cur->right) {
            printf("(RIGHT: %d %s)", to_int32(cur->right->value), (cur->right->colour == RED ? "RED" : "BLACK"));
            stack_push(&stk, cur->right);
        }
        printf("\n");
    }
    printf("END DEBUG\n");
}

rbtree new_rbtree(int32_t (* cmp) (void* x, void* y)) {
    return (rbtree) {
        .cmp  = cmp,
        .root = NULL,
        .size = 0
    };
}

bool rbtree_direction(rbtree* tree, void* node_value, void* value) {
    return tree->cmp(node_value, value) <= 0 ? RIGHT : LEFT;
}

void* rbtree_ll_rotation(rbtree_node* cur, rbtree_node* par, rbtree_node* grand, rbtree_node* unc) {
    rbtree_node* tmp = par->right;
    par->right = grand;
    grand->left = tmp;
    rbtree_switch_colour(par);
    rbtree_switch_colour(grand);
    return par;
}

void* rbtree_rr_rotation(rbtree_node* cur, rbtree_node* par, rbtree_node* grand, rbtree_node* unc) {
    rbtree_node* tmp = par->left;
    par->left = grand;
    grand->right = tmp;
    rbtree_switch_colour(par);
    rbtree_switch_colour(grand);
    return par;
}

void* rbtree_lr_rotation(rbtree_node* cur, rbtree_node* par, rbtree_node* grand, rbtree_node* unc) {
    rbtree_node* tmp = cur->left;
    cur->left = par;
    par->right = tmp;
    grand->left = cur;
    rbtree_ll_rotation(par, cur, grand, unc);
    return cur;
}

void* rbtree_rl_rotation(rbtree_node* cur, rbtree_node* par, rbtree_node* grand, rbtree_node* unc) {
    rbtree_node* tmp = cur->right;
    printf("8=D");
    cur->right = par;
    par->left = tmp;
    grand->right = cur;
    rbtree_rr_rotation(par, cur, grand, unc);
    return cur;
}

rbtree_node* rbtree_rotate(rbtree_node* cur, rbtree_node* par, rbtree_node* grand) {
    rbtree_node* unc = par == grand->left ? grand->right : grand->left;
    if (rbtree_is_red(unc)) {
        // only recolouring
        rbtree_switch_colour(unc);
        rbtree_switch_colour(par);
        rbtree_switch_colour(grand);
        return grand;
    }
    // rotation & recolouring
    if (cur == par->left) {
        if (par == grand->left) {
            return rbtree_ll_rotation(cur, par, grand, unc);
        } else {
            return rbtree_lr_rotation(cur, par, grand, unc);
        }
    } else {
        if (par == grand->right) {
            return rbtree_rr_rotation(cur, par, grand, unc);
        } else {
            return rbtree_rl_rotation(cur, par, grand, unc);
        }
    }
    return grand;
}

void rbtree_insert_impl(rbtree* tree, void* value) {
    if (!tree->root) {
        tree->root = new_rbtree_node(value);
        rbtree_switch_colour(tree->root);
        tree->size++;
        return;
    }
    stack stk = new_stack();
    rbtree_node* cur      = tree->root;
    rbtree_node* new_node = NULL;
    while (true) {
        stack_push(&stk, cur);
        bool dir = rbtree_direction(tree, cur->value, value);
        if (dir == LEFT) {
            printf("%d esquerda de %d\n", to_int32(value), to_int32(cur->value));
            if (!cur->left) {
                new_node = cur->left = new_rbtree_node(value);
                break;
            }
            cur = cur->left;
        } else {
            printf("%d direita de %d\n", to_int32(value), to_int32(cur->value));
            if (!cur->right) {
                new_node = cur->right = new_rbtree_node(value);
                break;
            }
            cur = cur->right;
        }
    }
    cur = new_node;
    while (stack_size(&stk) > 1) {
        rbtree_node* par   = (rbtree_node *) stack_pop(&stk);
        rbtree_node* grand = (rbtree_node *) stack_pop(&stk);
        rbtree_node* great = NULL;
        bool dir = LEFT;
        if (stack_size(&stk)) {
            great = stack_top(&stk);
            dir = grand == great->left ? LEFT : RIGHT;
        }
        if (!rbtree_has_same_colour(cur, par)) {
            break;
        }
        rbtree_node* new_grand = grand;
        if (rbtree_is_red(cur) && rbtree_is_red(par)) {
            new_grand = rbtree_rotate(cur, par, grand);
            // TODO
            // edge case: grand == root
            if (stack_empty(&stk)) {
                tree->root = new_grand;
            }
            if (great) {
                if (dir == LEFT) {
                    great->left = new_grand;
                } else {
                    great->right = new_grand;
                }
            }
        } else break;
        cur = new_grand;
    }
    tree->root->colour = BLACK;
    tree->size++;
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