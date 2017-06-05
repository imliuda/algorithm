#include <stdio.h>
#include <stdlib.h>

typedef struct _avl_tree avl_tree_t;

struct _avl_tree {
    int         key;
    int         height;
    void        *data;
    avl_tree_t  *parent;
    avl_tree_t  *left;
    avl_tree_t  *right;
};

avl_tree_t *avl_tree_new() {
    return NULL;
}

int avl_tree_height(avl_tree_t *root) {
    int left, right;
    if (root == NULL) {
        return 0;
    }
    printf ("%d_", root->key);
    left = avl_tree_height(root->left) + 1;
    right = avl_tree_height(root->right) + 1;
    return left > right ? left : right;
}

// inline
avl_tree_t * avl_tree_insert(avl_tree_t *root, avl_tree_t *node) {
    avl_tree_t *parent, *child;
    int node_height, child_height;
    
    node->left = node->right = NULL;

    if (root == NULL) {
        node->parent = NULL;
        node->height = 1;
        root = node;
        return;
    }

    if (node->key <= root->key) {
        if (root->left == NULL) {
            node->parent = root;
            node->height = root->height + 1;
            root->left = node;
            printf("insert left\n");
/*
            // rotate
            parent = root;
            node_height = 0;
            while (parent->parent != NULL) {
                node_height++;
                child = parent->parent->left == parent ? parent->parent->right : parent;
                child_height = 0;
                do {
                    child_height++;
                } while(child->left || child->right);

                parent = parent->parent;
            };
*/
        } else {
            avl_tree_insert(root->left, node);
        }
    } else {
        if (root->right == NULL) {
            node->parent = root;
            node->height = root->height + 1;
            root->right = node;
            printf("insert right\n");
        } else {
            avl_tree_insert(root->right, node);
        }
    }

    return root;
}

int main() {
    avl_tree_t *root = avl_tree_new();

    srandom(time(NULL));    
    int i;
    for(i=0; i<10; i++) {
        avl_tree_t *node = malloc(sizeof(avl_tree_t));
        node->key = random() % 100;
        printf("%d ", node->key);
        root = avl_tree_insert(root, node);
    }

    printf("tree height: %d\n", avl_tree_height(root));

    return 0;
}
