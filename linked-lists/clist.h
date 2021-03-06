#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

// structure for circular list elements
typedef struct CListElmt_ {
    void *data;
    struct CListElmt_ *next;
} CListElmt;

// struct for circular lists
typedef struct CList_ {
    int size;
    int (*match) (const void *key1, const void *key2);
    void (*destroy) (void *data);
    CListElmt *head;
} CList;

void clist_init(CList *list, void (*destroy) (void *data));

void clist_destroy(CList *list);

int clist_ins_next(CList *list, CListElmt *element, const void *data);

int clist_rem_next(CList *list, CListElmt *element, void **data);

#define clist_size(list) ((list)->size)

#define clist_head(list) ((list)->head)

#define clist_data(element) ((element)->data)

#define clist_next(element) ((element)->next)

void clist_init(CList *list, void (*destroy) (void *data)) {
    // initialize the list
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;

    return;
}

void clist_destroy(CList *list) {
    void *data;

    while (clist_size(list) > 0) {
        if (clist_rem_next(list, list->head, (void **)&data) == 0 && list->destroy != NULL)
            list->destroy(data);
    }

    memset(list, 0, sizeof(CList));
    return;
}

int clist_ins_next(CList *list, CListElmt *element, const void *data) {
    CListElmt *new_element;

    if ((new_element = (CListElmt *)malloc(sizeof(CListElmt))) == NULL)
        return -1;

    new_element->data = (void *)data;

    // if the list is empty
    if (clist_size(list) == 0) {
        // the head is the new element itself
        new_element->next = new_element;
        list->head = new_element;
    }

    else {
        new_element->next = element->next;
        element->next = new_element;
    }
    
    list->size++;
    return 0;
}

int clist_rem_next(CList *list, CListElmt *element, void **data) {
    CListElmt *old_element;

    // do not allow removal from an empty list
    if (clist_size(list) == 0)
        return -1;

    *data = element->next->data;
    old_element = element->next;

    if (old_element == element) {
        // handle removing the last element
        list->head = NULL;
    }

    else {
        element->next = element->next->next;
        if (old_element == clist_head(list))
            list->head = old_element->next;
    }

    free(old_element);
    list->size--;
    return 0;
}
#endif
