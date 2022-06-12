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

#endif
