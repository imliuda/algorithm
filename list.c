#include <stdlib.h>

#include "list.h"

/** 
 * create a new list.
 *
 * @return the head node of the new list.
 */
list *list_new() {
    list *list = malloc(sizeof(list));
    list->next = list;
    list->prev = list;
    return list;
}

void list_prepend(list *list, list *node) {
    list->next->prev = node;
    node->prev = list;
    node->next = list->next;
    list->next = node;
}

/**
 * insert a new element to a list.
 *
 * @param list a pointer to a list.
 * @param node the new element.
 */
void list_append(list *list, list *node) {
    list->prev->next = node;
    node->prev = list->prev;
    node->next = list;
    list->prev = node;
}

/**
 * insert a element before a element.
 *
 * @param cur after this element.
 * @param node the new element.
 */
void list_insert_before(list *cur, list *node) {
    cur->prev->next = node;
    node->prev = cur->prev;
    node->next = cur;
    cur->prev = node;
}

/**
 * insert a element after a element.
 *
 * @param cur after this element.
 * @param node the new element.
 */
void list_insert_after(list *cur, list *node) {
    cur->next->prev = node;
    node->next = cur->next;
    node->prev = cur;
    cur->next = node;
}

/** 
 * remove a element from list.
 *
 * @param list a pointer to a list
 * @param node node to be removed from the list
 */
void list_remove(list *list, list *node) {
    list *p = list->next;
    // if really need check?
    while (p != list) {
        if (p == node) {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
    }
}

/**
 * return the first element of the list.
 *
 * @param list a pointer to a list
 * @return the first element or NULL
 */
list *list_first(list *list) {
    if (list->next == list) {
        return NULL;
    }
    return list->next;
}

/**
 * return the last element of the list.
 *
 * @param list a pointer to a list
 * @return the last element or NULL
 */
list *list_last(list *list) {
    if (list->prev == list) {
        return NULL;
    }
    return list->prev;
}

/**
 * return the next node of current node.
 *
 * @see list_next
 */
list *list_prev(list *list, list *node) {
    if (node->prev == list) {
        return NULL;
    }
    return node->prev;
}

/**
 * return the next node of current node.
 *
 * this function can be used to iterate a list:
 *
 * list *p = list;
 * while (p = list_next(list, p)) {
 *     // do something
 * }
 *
 * or use iterate a list reverse:
 *
 * list *p = list;
 * while (p = list_prev(list, p)) {
 *     // do something
 * }
 *
 * @param list a pointer to a list
 * @param node current node
 * @return return the next node of current or NULL if current
 * node is the last.
 */
list *list_next(list *list, list *node) {
    if (node->next == list) {
        return NULL;
    }
    return node->next;
}

size_t list_length(list *list) {
    size_t len = 0;
    list *p = list->next;
    while (p != list) {
    	len++;
        p = p->next;
    }
    return len;
}

void list_sort(list *list, int (*compare)(list *node1, list *node2)) {

}

void list_foreach(list *list, void (*foreach)(list *node, void *data), void *data) {
    list *p = list->next;
    while (p != list) {
    	foreach(p, data);
    }
}

void list_free(list *list) {
    list *p = list->next;
    while (p != list) {
    	free(p);
    }
    free(list);
}
