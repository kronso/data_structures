#include <stdlib.h>

#include "../include/list.h"

#include "../include/log_errors.h"

/**
 * list_push_front:
 * @params: @list: pointer to list needed to modify.
 *          @val:  value that is to be stored into the list.
 * 
 * Creates a new node which then stores given value.
 * Uses _next to point to the current head,
 * then assign the current head to the new node.
*/
void list_push_front(List* list, void* val) { 
    if (list)
    {
        Node* new_head = malloc(sizeof(Node));
        new_head->_val = val;

        if (list->_head == NULL)
        {
            list->_head = list->_tail = new_head;
        }
        else 
        {
            new_head->_next = list->_head;
            list->_head->_prev = new_head;
            new_head->_prev = NULL;
            
            list->_head = new_head;
        }
        list->_size++;
    }
    else 
        LOG(E_OBJECT_UNINITIALIZED);
}
/**
 * list_pop_front:
 * @params: @list: pointer to list needed to modify.
 * 
 * Removes the current head and then assign it
 * to the next node.
 * Free list the nullify.
*/
void list_pop_front(List* list) {
    if (list)
    {
        if (list->_head != NULL)
        {
            list->_head = list->_head->_next;
            free(list->_head->_prev);
            list->_head->_prev = NULL;

            list->_size--;
        }
        else 
            LOG(E_SEGMENTATION_FAULT);
    }
    else 
        LOG(E_OBJECT_UNINITIALIZED);

}
/**
 * list_push_back:
 * @params: @list: pointer to list needed to modify.
 * 
 * Removes the current head and then assign it
 * to the next node.
*/
void list_push_back(List* list, void* val) { 
    if (list)
    {
        Node* new_tail = malloc(sizeof(Node));
        new_tail->_val = val;

        if (!list->_tail) 
        {
            list->_head = list->_tail = new_tail;
        } 
        else 
        {
            list->_tail->_next = new_tail;
            new_tail->_prev = list->_tail;
            new_tail->_next = NULL;

            list->_tail = new_tail;
        }
        list->_size++;
    }
    else 
        LOG(E_OBJECT_UNINITIALIZED);
}
/**
 * list_pop_back:
 * @params: @list: pointer to list needed to modify.
 * 
 * Removes the current tail and then assign it
 * to the previous node.
*/
void list_pop_back(List* list) { 
    if (list)
    {
        if (list->_tail)
        {
            free(list->_tail);
            list->_tail = list->_tail->_prev;
            list->_tail->_next = NULL;

            list->_size--;
        }
        else 
            LOG(E_SEGMENTATION_FAULT);
    }
    else 
        LOG(E_OBJECT_UNINITIALIZED);
}
/**
 * list_insert:
 * @params: @list: pointer to list needed to modify.
 *          @val:  pointer to value to insert into the given list.
 *          @pos:  position to insert the value.
 * 
 * Creates a new node and assigns the given value to insert 
 * at the given position. 
*/
void list_insert(List* list, void* val, unsigned pos) { 
    if (list)
    {
        if (pos > list->_size - 1 || list->_size == 0)
            LOG(E_INDEX_OUT_OF_BOUNDS);

        if (!pos)
        {
            list_push_front(list, val);
            return;
        }

        Node* node = list->_head;
        while (pos)
        {   
            --pos;
            node = node->_next;
        }  
        Node* new_node = malloc(sizeof(Node));
        new_node->_val = val;

        new_node->_prev = node->_prev;
        new_node->_prev->_next = new_node;
        new_node->_next = node;
        node->_prev = new_node;

        list->_size++;
    }
    else 
        LOG(E_OBJECT_UNINITIALIZED);
}
/**
 * list_erase:
 * @params: @list: pointer to list needed to modify.
 *          @pos:  position to erase the value.
 *
 * Link the next and previous nodes then deattach the
 * node at the given position and frees it. 
*/
void list_erase(List* list, unsigned pos) { 

    if (list)
    {
        if (pos > list->_size - 1 || list->_size == 0)
            LOG(E_INDEX_OUT_OF_BOUNDS);

        if (!pos)
        {
            list_pop_front(list);
            return;
        }
        else if (pos == list->_size - 1)
        {
            list_pop_back(list);
            return;
        }

        Node* node = list->_head;
        while (pos)
        {   
            --pos;
            node = node->_next;
        }  
        node->_prev->_next = node->_next;
        node->_next->_prev = node->_prev;
        free(node);

        list->_size--;
    }
    else 
        LOG(E_OBJECT_UNINITIALIZED);
}
/**
 * list_clear:
 * @params: @list: pointer to list needed to modify.
 *
 * Traverses through the list recursively and frees the nodes
 * until the list is empty. 
*/
void list_clear(List* list) { 
    if (list)
    {
        if (list->_size != 0) 
        {
            Node* node = list->_head;
            list->_head = list->_head->_next;
            free(node);
            list->_size--;

            list_clear(list);
        }
        list->_head = list->_tail = NULL;
    }
    else 
        LOG(E_OBJECT_UNINITIALIZED);
}
/**
 * list_size:
 * @params: @list: pointer to list needed to access properties.
 * 
 * Returns length of list.
*/
size_t list_size(List* list) {
    if (!list)
        LOG(E_OBJECT_UNINITIALIZED);
    return list->_size;
}
/**
 * list_empty:
 * @params: @list: pointer to list needed to access properties.
 *
 * Checks whether the list is empty and returns true or false.
*/
unsigned list_empty(List* list) { 
    if (!list)
        LOG(E_OBJECT_UNINITIALIZED);
    return (list->_size == 0) ? 1: 0;
}
/**
 * list_front:
 * @params: @list: pointer to list needed to access properties.
 * 
 * Returns the value at the front of the list.
*/
void* list_front(List* list) {
    if (!list)
        LOG(E_OBJECT_UNINITIALIZED); 

    if (list_empty(list))
        LOG(E_SEGMENTATION_FAULT);
    return list->_head->_val;
}
/**
 * list_back:
 * @params: @list: pointer to list needed to access properties.
 * 
 * Returns the value at the back of the list.
*/
void* list_back(List* list) {
    if (!list)
        LOG(E_OBJECT_UNINITIALIZED);

    if (list_empty(list))
        LOG(E_SEGMENTATION_FAULT);
    return list->_tail->_val;
}
/**
 * list_new:
 * 
 * Creates a list pointer and initializes its properties to 
 * zero's and returns it.
*/
List* list_new() { 
    List* list = malloc(sizeof(List));

    if (!list)
        LOG(E_SEGMENTATION_FAULT);

    *list = (List) { 0 };
    return list;
}
/**
 * list_destroy:
 * 
 * Uses list_clear function to recursivly free the nodes
 * and then frees the given list.
*/
void* list_destroy(List* list) {
    list_clear(list);
    free(list);
    return NULL;
}