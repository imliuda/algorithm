#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {RED, BLACK} COLOR;
typedef struct _rb_node rb_node;

struct _rb_node {
    int         key; // use int key for convernient
    void        *data;
    rb_node     *parent;
    rb_node     *left;
    rb_node     *right;
    COLOR        color;
};

void print_rbtree(rb_node *tree);
rb_node *rb_tree_new();
void rb_tree_delete(rb_node *tree);
void rb_tree_insert(rb_node **tree, rb_node *node);

/*
 * a pointer to the root node of a tree.
 */
rb_node *rb_tree_new() {
    return NULL;
}

void rb_tree_delete(rb_node *tree) {
}

static void _rb_tree_insert(rb_node **tree, rb_node *node) {
    if (*tree == NULL) {
        node->left= NULL;
        node->right = NULL;
        node->color = RED;
        *tree = node;
    } else if (node->key < (*tree)->key) {
        node->parent = *tree;
        _rb_tree_insert(&(*tree)->left, node); // &((*tree)->left)        
    } else {
        node->parent = *tree;
        _rb_tree_insert(&(*tree)->right, node);
    }
}

static void rotate_left(rb_node *node) {
    rb_node *p = node->parent, *left = node->left;
    node->parent = p->parent;
    node->left = p;
    p->parent = node;
    p->right = left;
}

void rotate_right(rb_node *node) {
    rb_node *p = node->parent, *right = node->right;
    node->parent = p->parent;
    node->right = p;
    p->parent = node;
    p->left = right;
}

static void _rb_tree_insert1(rb_node **root, rb_node *node);

static void _rb_tree_insert5(rb_node **root, rb_node *node) {
    node->parent->color = BLACK;
    node->parent->parent->color = RED;

    if (node == node->parent->left) {
        rotate_right(node->parent);
        if (node->parent->parent != NULL) {
            node->parent->parent->left = node->parent;
        }
    } else {
        rotate_left(node->parent);
        if (node->parent->parent != NULL) {
            node->parent->parent->right = node->parent;
        }
    }

    if (node->parent->parent == NULL) {
       *root = node->parent;
    }
}

static void _rb_tree_insert4(rb_node **root, rb_node *node) {
    rb_node *g = node->parent->parent;
    if ((node == node->parent->right) && (node->parent == g->left)) {
        rotate_left(node);
        node->parent->left = node;
        node = node->left;
    } else if ((node == node->parent->left) && (node->parent == g->right)) {
        rotate_right(node);
        node->parent->right = node;
        node = node->right;
    }
    _rb_tree_insert5(root, node);
}

static void _rb_tree_insert3(rb_node **root, rb_node *node) {
    rb_node *u = node->parent == node->parent->parent->left ?
                 node->parent->parent->right :
                 node->parent->parent->left;
    if (u && u->color == RED) {
        node->parent->color = BLACK;
        u->color = BLACK;
        u->parent->color = RED;
        _rb_tree_insert1(root, u->parent);
    } else {
        _rb_tree_insert4(root, node);
    }
}

static void _rb_tree_insert2(rb_node **root, rb_node *node) {
    if (node->parent->color == BLACK) {
        // do nothing
    } else {
        _rb_tree_insert3(root, node);
    }
}

static void _rb_tree_insert1(rb_node **root, rb_node *node) {
    if (node->parent == NULL) {
        node->color = BLACK;
    } else {
        _rb_tree_insert2(root, node);
    }
}

/**
 * insert a node to a tree.
 * 
 * @param tree the root node of a tree. when inserting, the root of
 * a tree may change, so we pass a double pointer to the function.
 */
void rb_tree_insert(rb_node **tree, rb_node *node) {
    _rb_tree_insert(tree, node);
    _rb_tree_insert1(tree, node);
}


/**
 * below belongs to main function of this file
 * there is no relation with rb tree
 */

void key(rb_node *tree, char *key) {
    if (tree == NULL)
        strcpy(key, "null");
    else
        snprintf(key, 32, "%d", tree->key);
}

void color(rb_node *tree, char *color) {
    if (tree == NULL)
        strcpy(color, "null");
    else
        snprintf(color, 32, tree->color == RED ? "red" : "black");
}

void print_rbtree(rb_node *tree) {
    char vkey[32], vparent[32], vleft[32], vright[32], vcolor[32];
    if (tree != NULL) {
        key(tree, vkey);
        key(tree->parent, vparent);
        key(tree->left, vleft);
        key(tree->right, vright);
        color(tree, vcolor);
        printf("current: %s, left: %s, right: %s, parent: %s, color: %s\n", vkey, vleft, vright, vparent, vcolor);

        if (tree->left) {
            print_rbtree(tree->left);
        }
        if (tree->right) {
            print_rbtree(tree->right);
        }
    }
}

int main() {
    rb_node *tree = rb_tree_new();
    rb_node *node;

//    srandom(time(NULL));    
    int i;
    //for(i=0; i<7; i++) {
      //  int num = random() % 100;
       // printf("%d\n", num);
        node = malloc(sizeof(rb_node));
        node->key = 9;
        rb_tree_insert(&tree, node);
        node = malloc(sizeof(rb_node));
        node->key = 8;
        rb_tree_insert(&tree, node);
        node = malloc(sizeof(rb_node));
        node->key = 7;
        rb_tree_insert(&tree, node);
        node = malloc(sizeof(rb_node));
        node->key = 6;
        rb_tree_insert(&tree, node);
        node = malloc(sizeof(rb_node));
        node->key = 5;
        rb_tree_insert(&tree, node);
       node = malloc(sizeof(rb_node));
        node->key = 4;
        rb_tree_insert(&tree, node);
        node = malloc(sizeof(rb_node));
        node->key = 3;
        rb_tree_insert(&tree, node);
        node = malloc(sizeof(rb_node));
        node->key = 2;
        rb_tree_insert(&tree, node);
    //}

    print_rbtree(tree);
    return 0;
}
