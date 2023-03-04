#include "array_list.h"
#include <stdlib.h>
#include <string.h>

ArrayList *alist_initialize(int maxSize, int itemSize, char *type) {
    ArrayList *list = malloc(sizeof(ArrayList));

    list->arr = malloc(maxSize * sizeof(void *));
    list->size = 0;
    list->maxSize = maxSize;
    list->itemSize = itemSize;
    list->type = type;

    return list;
}

bool alist_add(ArrayList *list, void *e) {
    if (list == NULL || e == NULL)
        return false;

    if (list->size == list->maxSize)
        _alist_resize(list);

    void *add = malloc(list->itemSize);
    memcpy(add, e, list->itemSize);
    list->arr[list->size++] = add;
    return true;
}

void *alist_get(ArrayList *list, int index) {
    if (list == NULL || index < 0 || index >= list->size)
        return NULL;

    void *get = malloc(list->itemSize);
    memcpy(get, list->arr[index], list->itemSize);
    return get;
}

int alist_index_of(ArrayList *list, void *e) {
    if (list == NULL || e == NULL)
        return -1;

    for (int i = 0; i < list->size; i++) {

        if (memcmp(list->arr[i], e, list->itemSize) == 0)
            return i;
    }
    return -1;
}

bool alist_add_at(ArrayList *list, int index, void *e) {
    if (list == NULL || e == NULL || index < 0 || index > list->size)
        return false;

    if (index == list->size)
        return alist_add(list, e);
    if (list->size == list->maxSize)
        _alist_resize(list);

    for (int i = list->size - 1; i >= index; i--) {
        list->arr[i + 1] = list->arr[i];
    }

    void *add = malloc(list->itemSize);
    memcpy(add, e, list->itemSize);
    list->arr[index] = add;
    list->size++;
    return true;
}

void *alist_remove(ArrayList *list, int index) {
    if (list == NULL || index < 0 || index >= list->size)
        return NULL;

    void *remove = malloc(list->itemSize);
    memcpy(remove, list->arr[index], list->itemSize);

    for (int i = index; i < list->size - 1; i++) {
        list->arr[i] = list->arr[i + 1];
    }

    list->size--;
    return remove;
}

void alist_clear(ArrayList *list) {
    if (list == NULL)
        return;

    for (int i = 0; i < list->size; i++) {
        free(list->arr[i]);
        list->arr[i] = NULL;
    }
    list->size = 0;
}

bool alist_destroy(ArrayList *list) {
    if (list == NULL)
        return false;

    alist_clear(list);

    free(list->arr);
    list->arr = NULL;
    free(list);
    list = NULL;

    return true;
}

bool _alist_resize(ArrayList *list) {
    if (list == NULL)
        return false;

    list->maxSize *= 2;

    void **temp = realloc(list->arr, list->maxSize * list->itemSize);
    if (temp == NULL)
        return false;

    list->arr = temp;
    return true;
}


