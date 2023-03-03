#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

LinkedList *llist_initialize(int itemSize, char *type) {
    LinkedList *list = malloc(sizeof(LinkedList));

    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    list->itemSize = itemSize;
    list->type = type;

    return list;
}

bool llist_add_at(LinkedList *list, int index, void *e) {
    if (list == NULL || e == NULL)
        return false;

    if (index == 0) {
        llist_add_first(list, e);
        return true;
    }

    if (index >= list->size) {
        llist_add_last(list, e);
        return true;
    }

    Node *curr = list->first;
    for (int i = 1; i < index; i++) {
        curr = curr->next;
    }

    Node *add = malloc(sizeof(Node));
    add->data = e;
    add->prev = curr;
    add->next = curr->next;
    curr->next = add;
    curr->next->prev = add;

    list->size++;
    return true;
}

bool llist_add_first(LinkedList *list, void *e) {
    if (list == NULL || e == NULL)
        return false;

    Node *add = malloc(sizeof(Node));
    add->data = e;
    add->prev = NULL;

    if (list->first == NULL) {
        list->first = add;
        list->last = add;
        add->next = NULL;
    } else {
        list->first->prev = add;
        add->next = list->first;
        list->first = add;
    }

    list->size++;
    return true;
}

bool llist_add_last(LinkedList *list, void *e) {
    Node *add = malloc(sizeof(Node));
    add->data = e;
    add->next = NULL;

    if (list->last == NULL) {
        list->first = add;
        list->last = add;
        add->prev = NULL;
    } else {
        list->last->next = add;
        add->prev = list->last;
        list->last = add;
    }

    list->size++;
    return true;
}

void *llist_get(LinkedList *list, int index) {
    if (list == NULL || index < 0 || index >= list->size || list->first == NULL)
        return NULL;

    Node *curr = list->first;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    return curr->data;
}

int llist_index_of(LinkedList *list, void *e) {
    if (list == NULL || e == NULL || list->first == NULL)
        return -1;

    Node *curr = list->first;
    for (int i = 0; i < list->size; i++) {
        if (memcmp(curr->data, e, list->itemSize) == 0)
            return i;

        curr = curr->next;
    }
    return -1;
}

void *llist_remove(LinkedList *list, int index) {
    if (list == NULL || index < 0 || index >= list->size || list->first == NULL)
        return NULL;
    
    if (index == 0) {
        return llist_remove_first(list);
    } else if (index == list->size - 1)
        return llist_remove_last(list);
    
    Node *curr = list->first;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    
    void *data = curr->data;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    curr->next = NULL;
    curr->prev = NULL;
    free(curr);
    curr = NULL;
    
    list->size--;
    return data;
}

void *llist_remove_first(LinkedList *list) {
    if (list == NULL || list->first == NULL)
        return NULL;
    
    if (list->size == 1) {
        void *data = list->first->data;
        free(list->first);
        list->first = NULL;
        list->last = NULL;
        list->size--;
        return data;
    }
    
    void *data = list->first->data;
    list->first = list->first->next;
    free(list->first->prev);
    list->first->prev = NULL;
    list->size--;
    return data;
}

void *llist_remove_last(LinkedList *list) {
    if (list == NULL || list->first == NULL)
        return NULL;
    
    if (list->size == 1) {
        void *data = list->first->data;
        free(list->first);
        list->first = NULL;
        list->last = NULL;
        list->size--;
        return data;
    }

    void *data = list->last->data;
    list->last = list->last->prev;
    free(list->last->next);
    list->last->next = NULL;
    list->size--;
    return data;
}

bool llist_destroy(LinkedList *list) {
    if (list == NULL)
        return false;
    
    void *ptr = llist_remove_first(list);
    while (ptr != NULL) {
        ptr = llist_remove_first(list);
    }
    
    free(list);
    list = NULL;
    return true;
}

