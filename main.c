#include "rbtree.h"

int cmp(void* x, void* y) {
    return *(int *)x - *(int *)y;
}

int main(int argc, char** argv) {
    rbtree tree = new_rbtree(cmp);
    for (int i = 1; i <= 10; i++) {
        rbtree_insert(&tree, i);
    }
    debug(&tree);
    printf("END\n");
    return EXIT_SUCCESS;
}