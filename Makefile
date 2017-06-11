all: avl_tree rb_tree

avl_tree: avl_tree.c
	gcc -g -o avl_tree avl_tree.c

rb_tree: rb_tree.c
	gcc -g -o rb_tree rb_tree.c

clean:
	rm -rf avl_tree rb_tree *.o

.PHONY: all clean
