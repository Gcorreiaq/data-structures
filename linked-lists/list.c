#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

void list_init(List *list, void (*destroy) (void *data)) {
    //just initializes the list

    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    
    return;
}

void list_destroy(List *list) {
    void *data;

    while (list_size(list) > 0) {
        // call user-defined destroy function for *data 
        if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL)
            list->destroy(data);
    }
    memset(list, 0, sizeof(List));
    return;
}

int list_ins_next(List *list, ListElmt *element, const void *data) {
    ListElmt *new_element;

    if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
        return -1;

    // new element points to *data 
    new_element->data = (void *)data;

    // if element == NULL, insert at the head of the list
    if (element == NULL) {
        // if list is empty, the head is the tail too
        if (list_size(list) == 0)
            list->tail = new_element;
        
        new_element->next = list->head;
        list->head = new_element;
    }
    // insert elsewhere
    else {
        // if element->next == NULL, the new element will be the tail
        if (element->next == NULL)
            list->tail = new_element;

        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;
    return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data) {
    ListElmt *old_element;
    // if list is empty, do nothing
    if (list_size(list) == 0)
        return -1;
    // remove the head
    if (element == NULL) {
        // the data will be saved
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;
        // if list is going to be empty, null the tail pointer
        if (list_size(list) == 1)
            list->tail = NULL;
    }
    
    else {
        // if you want to remove the tail, pass the preceding element in the element parameter
        if (element->next == NULL)
            return -1;
        // the next element is the element to be removed, so we save its data
        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;
        // it means the element is now the tail
        if (element->next == NULL)
            list->tail = element;
    }

    free(old_element);
    list->size--;
    return 0;
}


int main () {
    
    printf("test");
    return 0;
}
