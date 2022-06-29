#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "../linked-lists/list.h"

typedef List Queue;

// since a queue is a linked list and requires the same initialization, queue_init is defined to list_init.
#define queue_init list_init

#define queue_destroy list_destroy

int queue_enqueue(Queue *queue, const void *data);

int queue_dequeue(Queue *queue, void **data);

#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)

#define queue_size list_size

int queue_enqueue(Queue *queue, const void *data) {
    return list_ins_next(queue, list_tail(queue), data);
}

int queue_dequeue(Queue *queue, void **data) {
    return list_rem_next(queue, NULL, data);
}

#endif
