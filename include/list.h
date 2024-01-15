#pragma once
#include <stdio.h>

/**
 * Node:
 * @properties: @_val:  stores any value that is addressed in memory. 
 *              @_next: stores address of the next node.  
 *              @_prev: stores address of the previous node. 
*/              
typedef struct _ListNode ListNode;
struct _ListNode {
    void* _val;
    ListNode* _next;
    ListNode* _prev;
};
/**
 * List:
 * @properties: @_head: always stores the address of the first node in the list. 
 *              @_tail: always stores the address of the last node in the list.  
 *              @_size: stores the length of list.  
 * 
 * Doubly-linked list
 * List is sequential and does not loop back to the head.
*/       
typedef struct List { 
    ListNode  *_head, *_tail;
    size_t     _size;
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
size_t list_size     (List* list);
unsigned list_empty  (List* list);

/* Element access */
void* list_front     (List* list);
void* list_back      (List* list);

/* Constructor and destructor */
List* list_new       ();
void list_destroy   (List* list);