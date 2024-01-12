#pragma once
#include <stdio.h>
/**
 * Doubly-linked list
 * List is sequential and does not loop back to the head.
*/

/**
 * Node:
 * @properties: @_val:  stores any value that is addressed in memory. 
 *              @_next: stores address of the next node.  
 *              @_prev: stores address of the previous node. 
*/              
typedef struct _Node Node;
struct _Node {
    void* _val;
    Node* _next;
    Node* _prev;
};
/**
 * List:
 * @properties: @_head: always stores the address of the first node in the list. 
 *              @_tail: always stores the address of the last node in the list.  
 *              @_size: stores the length of list.  
*/       
typedef struct List { 
    Node*  _head;
    Node*  _tail;
    size_t _size;
} List;

/* Modifiers */
void list_push_front (List* list, void* val);
void list_pop_front  (List* list);
void list_push_back  (List* list, void* val);
void list_pop_back   (List* list);
void list_insert     (List* list, void* val, unsigned pos);
void list_erase      (List* list, unsigned pos);
void list_clear      (List* list);

/* Capacity */
unsigned list_empty  (List* list);
size_t list_size     (List* list);

/* Element access */
void* list_front     (List* list);
void* list_back      (List* list);

/* Constructor and destructor */
List* list_new       ();
void* list_destroy   (List* list);