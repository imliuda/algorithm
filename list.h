#ifndef __LIST_H__
#define __LIST_H__

typedef struct list list;

struct list {
    void    *data;
    list    *prev;
    list    *next;
};

list *list_new();
void list_prepend(list *list, list *node);
void list_append(list *list, list *node);
void list_insert_before(list *cur, list *node);
void list_insert_after(list *cur, list *node);
void list_remove(list *list, list *node);
list *list_first(list *list);
list *list_last(list *list);
list *list_prev(list *list, list *node);
list *list_next(list *list, list *node);
size_t list_length(list *list);
void list_sort(list *list, int (*compare)(list *node1, list *node2));
void list_foreach(list *list, void (*foreach)(list *node, void *data), void *data);
void list_free(list *list);

#endif
