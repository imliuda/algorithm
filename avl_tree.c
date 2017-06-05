#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a, b) ((a > b) ? (a) : (b))

typedef struct _avl_tree avl_tree;

struct _avl_tree {
    int         key;
    int         height;
    void        *data;
    avl_tree    *left;
    avl_tree    *right;
};

avl_tree *avl_tree_new() {
    return NULL;
}

int avl_tree_height(avl_tree **tree) {
    if (*tree == NULL) {
        return 0;
    }

    return (*tree)->height;
}

static void right_rotate(avl_tree *tree) {
    avl_tree *child = tree->left;
    tree->left = child->right;
    child->right = tree;

    tree->height = max(avl_tree_height(&tree->left),
                       avl_tree_height(&tree->right)) + 1;
    child->height = max(avl_tree_height(&child->left),
                       avl_tree_height(&child->right)) + 1;
}

static void left_rotate(avl_tree *tree) {
    avl_tree *child = tree->right;
    tree->right = child->left;
    child->left = tree;

    tree->height = max(avl_tree_height(&tree->left),
                       avl_tree_height(&tree->right)) + 1;
    child->height = max(avl_tree_height(&child->left),
                       avl_tree_height(&child->right)) + 1;
}

void avl_tree_insert(avl_tree **tree, int key, void *data) {
    if (*tree == NULL) {
        *tree = malloc(sizeof(avl_tree));
        (*tree)->key = key;
        (*tree)->data = data;
        (*tree)->height = 1;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
    } else if (key <= (*tree)->key) {
        avl_tree_insert(&(*tree)->left, key, data);
        if (avl_tree_height(&(*tree)->left) -
            avl_tree_height(&(*tree)->right) == 2) {
            if (key <= (*tree)->left->key) {
                right_rotate(*tree);
            } else {
                left_rotate((*tree)->left);
                right_rotate(*tree);
            }
        }
    } else {
        avl_tree_insert(&(*tree)->right, key, data);
         if (avl_tree_height(&(*tree)->right) -
            avl_tree_height(&(*tree)->left) == 2) {
            if (key > (*tree)->left->key) {
                left_rotate(*tree);
            } else {
                right_rotate((*tree)->right);
                left_rotate(*tree);
            }
        }
    }
    (*tree)->height = max(avl_tree_height(&(*tree)->left),
                          avl_tree_height(&(*tree)->right)) + 1;
}

/*
 * ┌ \u250c ┐ \u2510  ┴ \u2534  ─ \u2500
 */
static void _avl_tree_print_symbol(int padding, int width) {
    int i;
    for (i = 0 ; i <= width / 2; i++) {
        printf(" ");
    }
    printf("\u250c");
    for (i = 0 ; i <= width / 2; i++) {
        printf("\u2500");
    }
    printf("\u2534");
    for (i = 0 ; i <= width / 2; i++) {
        printf("\u2500");
    }
    printf("\u2510");
    printf("\n");
}

static void _avl_tree_print_fill(avl_tree **tree, char *buf[]) {
    
}

void avl_tree_print(avl_tree **tree) {
    int height = avl_tree_height(tree);
    char *buf[height];
    avl_tree *node = *tree;
    _avl_tree_print_symbol(10, 5);
    int i;
    for (i = 0; i < height; i++) {
        printf("");
    }
}

int main() {
    avl_tree *tree = avl_tree_new();

    srandom(time(NULL));    
    int i;
    for(i=0; i<10; i++) {
        avl_tree_insert(&tree, random() % 100, NULL);
    }

    printf("tree height: %d\n", avl_tree_height(&tree));
    //avl_tree_print(&tree);
    return 0;
}
