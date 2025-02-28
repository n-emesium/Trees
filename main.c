#include "tree.h"
int main(void) {
    tree *t = create(INT);
    int a = 42, b = 58, c = 99, new_value = 123;

    add(t, &a, "");  // Set root's value
    add(t, &b, "r");
    add(t, &c, "rl");





    printf("Tree contents:\n");
    stream(t);

    rmv(t, "r");
    printf("\nAfter removing right child:\n");
    stream(t);

    set(t, &new_value, "rl"); // Set right->left to 123
    printf("\nAfter setting new value at right->left:\n");
    stream(t);

    tree *t2 = create(INT);
    add(t2, &a, "");
    add(t2, &b, "r");
    add(t2, &new_value, "rl");

    if (equals(t, t2)) {
        printf("\nBoth trees are identical.\n");
    } else {
        printf("\nTrees are different.\n");
    }

    del(t);
    del(t2);
    return 0;
}
