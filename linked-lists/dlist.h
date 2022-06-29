#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

// structure for the elements of doubly-linked lists
typedef struct DlistElmt_ {
    void *data;
    struct DlistElmt_ *prev;
    struct DlistElmt_ *next;
} DListElmt;

// structure for doubly-linked lists
typedef struct DList_ {
    int size; //size of the list
    int (*match) (const void *key1, const void *key2);
    void (*destroy) (void *data); // user-defined function which is called when destructing the list
    DListElmt *head; // pointer to the head element
    DListElmt *tail; // pointer to the tail element
} DList;

// init the list and fills the 'list' structure provided by the caller. The second argument is optional, it is a user-defined function which is called when destructing the list.
void dlist_init(DList *list, void (*destroy) (void *data));

// destructs the list, after calling this function the list should not be used.
void dlist_destroy(DList *list);

// inserts an element after 'element' provided by the caller,
int dlist_ins_next(DList *list, DListElmt *element, const void *data);

// inserts an element before 'element' provided by the caller
int dlist_ins_prev(DList *list, DListElmt *element, const void *data);

// removes an element specified as 'element', 'data' points to the data stored by the removed element
int dlist_remove(DList *list, DListElmt *element, void **data);

// returns the list size
#define dlist_size(list) ((list)->size)

// returns the head of the list
#define dlist_head(list) ((list)->head)

// returns the tail of the list
#define dlist_tail(list) ((list)->tail)

// returns whether an element is the head or not
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)

// returns whether an element is the tail or not
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)

// returns the data stored by an element
#define dlist_data(element) ((element)->data)

// returns the next element of the specified element
#define dlist_next(element) ((element)->next)

// returns the previous element of the specified element
#define dlist_prev(element) ((element)->prev)

void dlist_init(DList *list, void (*destroy) (void *data)) {
    //initialize the list
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}

void dlist_destroy(DList *list) {
    
    void *data;
    
    while (dlist_size(list) > 0) {
        // remove the last element and calls the destroy function if not NULL 
        if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }
    
    memset(list, 0, sizeof(DList));
    return;
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data) {
    
    DListElmt *new_element;

    // do not allow a NULL element unless the list is empty
    if (element == NULL && dlist_size(list) != 0)
        return -1;
    if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
        return -1;

    new_element->data = (void *)data;
    
    if (dlist_size(list) == 0) {
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }

    else {
        new_element->next = element->next;
        new_element->prev = element;

        if (element->next == NULL)
            list->tail = new_element;
        else
            element->next->prev = new_element;

        element->next = new_element;
    }

    list->size++;
    return 0;
}

int dlist_ins_prev(DList *list, DListElmt *element, const void *data) {
    DListElmt *new_element;

    if (element == NULL && dlist_size(list) != 0)
        return -1;
    if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
        return -1;
    
    new_element->data = (void *)data;

    if (dlist_size(list) == 0) {
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }

    else {
        new_element->next = element;
        new_element->prev = element->prev;
        
        if (element->prev == NULL)
            list->head = new_element;
        else
            element->prev->next = new_element;

        element->prev = new_element;
    }

    list->size++;
    return 0;
}

int dlist_remove(DList *list, DListElmt *element, void **data) {
    if (element == NULL || dlist_size(list) == 0)
        return -1;

    *data = element->data;

    if (element == list->head) {
        list->head = element->next;

        if (list->head == NULL)
            list->tail == NULL;
        else
            element->next->prev = NULL;
    }

    else {
        element->prev->next = element->next;

        if (element->next == NULL)
            list->tail = element->prev;
        else
            element->next->prev = element->prev;
    }

    free(element);
    list->size--;
    return 0;
}

#endif
