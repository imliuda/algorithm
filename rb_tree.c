#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {RED, BLACK} COLOR;
typedef struct _rb_tree rb_tree;

struct _rb_tree {
    int         key; // use int key for convernient
    void        *data;
    rb_tree     *parent;
    rb_tree     *left;
    rb_tree     *right;
    COLOR        color;
};


/*
 * a pointer point to the root node of a tree.
 * if it is NULL, the tree is a empty.
 */
rb_tree *rb_tree_new() {
    return NULL;
}

void rb_tree_insert(rb_tree **tree, int key, void *data) {
    if (tree == NULL) {
        *tree = malloc(sizeof(rb_tree));
        (*tree)->data = data;
        (*tree)->parent = NULL;
        (*tree)->left= NULL;
        (*tree)->right = NULL;
        (*tree)->color = BLACK;
    } else {
        printf("uncle: %ld\n", uncle(*tree));
    }
}

/*
 * below belongs to main function of this file
 * there is no relation with rb tree
 */

void print_bintree(void *tree, void (*key)(void *, char *key), void *(*left)(void *), void *(*right)(void *));

void _key(void *tree, char *key) {
    if (tree == NULL)
        strcpy(key, "null");
    else
        snprintf(key, 32, "%d", ((rb_tree *)tree)->key);
}

static void *_left(void *tree) {
    return ((rb_tree *)tree)->left;
}

static void *_right(void *tree) {
    return ((rb_tree *)tree)->right;
}

int main() {
    rb_tree *tree = rb_tree_new();

//    srandom(time(NULL));    
    int i;
    //for(i=0; i<7; i++) {
      //  int num = random() % 100;
       // printf("%d\n", num);
        rb_tree_insert(&tree, 2, NULL);
        rb_tree_insert(&tree, 1, NULL);
        rb_tree_insert(&tree, 3, NULL);
/*        rb_tree_insert(&tree, 93, NULL);
        rb_tree_insert(&tree, 11, NULL);
        rb_tree_insert(&tree, 12, NULL);
        rb_tree_insert(&tree, 80, NULL);
        rb_tree_insert(&tree, 19, NULL);*/
    //}

    print_bintree(tree, _key, _left, _right);
    return 0;
}
