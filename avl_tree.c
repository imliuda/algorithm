#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static void right_rotate(avl_tree **tree) {
    avl_tree *child = (*tree)->left;
    (*tree)->left = child->right;
    child->right = *tree;

    (*tree)->height = max(avl_tree_height(&(*tree)->left),
                       avl_tree_height(&(*tree)->right)) + 1;
    child->height = max(avl_tree_height(&child->left),
                       avl_tree_height(&child->right)) + 1;

    *tree = child;
}

static void left_rotate(avl_tree **tree) {
    avl_tree *child = (*tree)->right;
    (*tree)->right = child->left;
    child->left = *tree;

    (*tree)->height = max(avl_tree_height(&(*tree)->left),
                       avl_tree_height(&(*tree)->right)) + 1;
    child->height = max(avl_tree_height(&child->left),
                       avl_tree_height(&child->right)) + 1;

    *tree = child;
}

void avl_tree_insert(avl_tree **tree, int key, void *data) {
    if (*tree == NULL) {
        *tree = malloc(sizeof(avl_tree));
        (*tree)->key = key;
        (*tree)->data = data;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
    } else if (key <= (*tree)->key) {
        avl_tree_insert(&(*tree)->left, key, data);
        if (avl_tree_height(&(*tree)->left) -
            avl_tree_height(&(*tree)->right) == 2) {
            if (key <= (*tree)->left->key) {
                right_rotate(tree);
            } else {
                left_rotate(&(*tree)->left);
                right_rotate(tree);
            }
        }
    } else {
        avl_tree_insert(&(*tree)->right, key, data);
         if (avl_tree_height(&(*tree)->right) -
            avl_tree_height(&(*tree)->left) == 2) {
            if (key > (*tree)->right->key) {
                left_rotate(tree);
            } else {
                right_rotate(&(*tree)->right);
                left_rotate(tree);
            }
        }
    }
    (*tree)->height = max(avl_tree_height(&(*tree)->left),
                          avl_tree_height(&(*tree)->right)) + 1;
}

/*
 * below belongs to main function of this file
 * there is no relation with avl tree
 */

void key(avl_tree *tree, char *key) {
    if (tree == NULL)
        strcpy(key, "null");
    else
        snprintf(key, 32, "%d", tree->key);
}

void print_bintree(avl_tree *tree) {
    char vkey[32], vleft[32], vright[32];
    if (tree != NULL) {
        key(tree, vkey);
        key(tree->left, vleft);
        key(tree->right, vright);
        printf("current: %s, left: %s, right: %s\n", vkey, vleft, vright);

        if (tree->left) {
            print_bintree(tree->left);
        }
        if (tree->right) {
            print_bintree(tree->right);
        }
    }
}

int main() {
    avl_tree *tree = avl_tree_new();

    srandom(time(NULL));    
    int i;
    //for(i=0; i<7; i++) {
      //  int num = random() % 100;
       // printf("%d\n", num);
        avl_tree_insert(&tree, 52, NULL);
        avl_tree_insert(&tree, 72, NULL);
        avl_tree_insert(&tree, 93, NULL);
        avl_tree_insert(&tree, 11, NULL);
        avl_tree_insert(&tree, 12, NULL);
        avl_tree_insert(&tree, 80, NULL);
        avl_tree_insert(&tree, 19, NULL);
    //}

    printf("tree height: %d\n", avl_tree_height(&tree));
    print_bintree(tree);
    return 0;
}
