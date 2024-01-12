#include <stdlib.h>

#include "../include/queue.h"

#include "../include/log_errors.h"

/**
 * enqueue:
 * @params: @queue: pointer to queue needed to modify.
 *          @val:   value that is to be stored onto the queue.
 * 
 * Appends @val to the back of the queue.
*/
void enqueue(Queue* queue, void* val) {
    if (queue)
    {
        if (!queue->_front)
        {
            queue->_front = malloc(sizeof(Node));
            queue->_front->_val = val;
            queue->_front->_next = NULL;

            queue->_back = queue->_front;
        }
        else 
        {
            Node* new_node = malloc(sizeof(Node));
            new_node->_val = val;
            queue->_back->_next = new_node;
            new_node->_next = NULL;

            queue->_back = new_node;
        }
        queue->_size++;
    }
    else 
        LOG(E_OBJECT_UNINITIALIZED);
}
/**
 * enqueue:
 * @params: @queue: pointer to queue needed to modify.
 * 
 * Removes the value at the front of the queue and 
 * assigns the previous front node to the next node.
*/
void deque(Queue* queue) {
    if (queue)
    {
        if (!queue_empty(queue))
        {   
            Node* temp = queue->_front;
            if (queue->_front->_next)
                queue->_front = queue->_front->_next;
            free(temp);
            queue->_size--;
        }
        else 
            LOG(E_SEGMENTATION_FAULT);
    }   
    else 
        LOG(E_OBJECT_UNINITIALIZED);
}
/**
 * queue_size:
 * @params: @queue: pointer to queue needed to access properties.
 * 
 * Returns the length of the queue.
*/
size_t queue_size(Queue* queue) { 
    if (!queue)
        LOG(E_OBJECT_UNINITIALIZED);
    return queue->_size;
}
/**
 * queue_empty:
 * @params: @queue: pointer to queue needed to access properties.
 * 
 * Checks whether the queue is empty and returns true or false.
*/
unsigned queue_empty(Queue* queue) {
    if (!queue)
        LOG(E_OBJECT_UNINITIALIZED);
    return (queue->_size == 0) ? 1: 0;
}
/**
 * queue_front:
 * @params: @queue: pointer to queue needed to access properties.
 * 
 * Returns the value at the front of the queue.
*/
void* queue_front(Queue* queue) { 
    if (!queue)
        LOG(E_OBJECT_UNINITIALIZED)

    if (queue_empty(queue))
        LOG(E_SEGMENTATION_FAULT);
    return queue->_front->_val;
}
/**
 * queue_back:
 * @params: @queue: pointer to queue needed to access properties.
 * 
 * Returns the value at the back of the queue.
*/
void* queue_back(Queue* queue) {
    if (!queue)
        LOG(E_OBJECT_UNINITIALIZED)

    if (queue_empty(queue))
        LOG(E_SEGMENTATION_FAULT);
    return queue->_back->_val;
}
/**
 * queue_new:
 * Creates a queue pointer and initializes its properties to
 * zero's and returns it.
*/
Queue* queue_new(void) { 
    Queue* queue = malloc(sizeof(Queue));

    if (!queue)
        LOG(E_SEGMENTATION_FAULT);

    *queue = (Queue) { 0 }; 
    return queue;
}
/**
 * queue_destroy:
 * @params: @queue: pointer to queue needed to access properties.
 * 
 * Iteratively free the nodes and then frees the given queue.
*/
void* queue_destroy(Queue* queue) { 
    if (!queue) 
        LOG(E_OBJECT_UNINITIALIZED);
        
    Node* node = queue->_front;
    while (node->_next)
    {
        node = queue->_front;
        
        queue->_front = queue->_front->_next;
        free(node);
        queue->_size--;
    }
    free(queue);
    return NULL;
}