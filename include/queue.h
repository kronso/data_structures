#pragma once
#include <stdio.h>

/**
 * Node:
 * @properties: @_val:  stores any value that is addressed in memory. 
 *              @_next: stores address of the next node.  
*/
typedef struct _Node Node;
struct _Node {
    void* _val;
    Node* _next;
};
/**
 * Queue:
 * @properties: @_front: always stores the address of the first node in the queue. 
 *              @_back:  always stores the address of the last node in the queue.  
 *              @_size:  stores the length of queue. 
 * 
 * List kinda implementation of a queue. 
*/ 
typedef struct _Queue { 
    Node  *_front, *_back;
    size_t _size;
} Queue;

/* Modifiers */
void enqueue            (Queue* queue, void* val);
void deque              (Queue* queue);

/* Capacity */
size_t queue_size       (Queue* queue);
unsigned queue_empty    (Queue* queue);

/* Element access */
void* queue_front       (Queue* queue);
void* queue_back        (Queue* queue);

/* Constructor and destructor */
Queue* queue_new        (void);
void* queue_destroy     (Queue* queue);