#include <stdlib.h>

#include "../include/stack.h"

#include "../include/log_errors.h"

/**
 * stack_push:
 * @params: @stack: pointer to stack needed to modify.
 *          @val:   value that is to be stored onto the stack.
 * 
 * Appends @val to the top of the stack.
*/
void stack_push(Stack* stack, void* val) { 
    if (stack)
    {
        if (stack->_size == 0)
        {
            stack->_arr = malloc(sizeof(void *));
            *(stack->_arr + stack->_size) = val;
            stack->_size++;
        }
        else 
        {
            stack->_size++;
            stack->_arr = realloc(stack->_arr, sizeof(void *) * stack->_size);       
            *(stack->_arr + stack->_size - 1) = val;
        }
    }
    else
        LOG(E_OBJECT_UNINITIALIZED);
}
/**
 * stack_pop:
 * @params: @stack: pointer to stack needed to modify.
 * 
 * Removes the value at the top of the stack.
 * (Realloc frees top of the stack i think).
*/
void stack_pop(Stack* stack) {  
    if (stack)
    {
        if (stack->_size == 0)
            LOG(E_SEGMENTATION_FAULT);
            
        stack->_size--;
        stack->_arr = (void **) realloc(stack->_arr, sizeof(void *) * stack->_size);
    }
    else 
        LOG(E_OBJECT_UNINITIALIZED);
} 
/**
 * stack_size:
 * @params: @stack: pointer to stack needed to access properties.
 * 
 * Returns length of stack.
*/
size_t stack_size(Stack* stack) {
    if (!stack)
        LOG(E_OBJECT_UNINITIALIZED);
    return stack->_size;
}
/**
 * stack_empty:
 * @params: @stack: pointer to stack needed to access properties.
 * 
 * Checks whether the stack is empty and returns true or false.
*/
unsigned stack_empty(Stack* stack) {
    if (!stack)
        LOG(E_OBJECT_UNINITIALIZED);
    return (stack->_size == 0) ? 1: 0;
}
/**
 * stack_top:
 * @params: @stack: pointer to stack needed to access properties.
 * 
 * Returns value at the top of the stack.
*/
void* stack_top(Stack* stack) {
    if (!stack)
        LOG(E_OBJECT_UNINITIALIZED);
    
    if (stack_empty(stack))
        LOG(E_SEGMENTATION_FAULT);
    return *(stack->_arr + stack->_size - 1);
}
/**
 * stack_new:
 * Creates a stack pointer and returns it.
 * The if statement is executed, the malloc function failed to...
 * allocate memory due to memory exhaustion - malloc not giving the desired space.
 * e.g allocating above available memory
 *     heap fragmentation - no contiguous blocks of memory of n size is available. 
 * 
 * It probably doesn't matter on a modern machine but hi.
*/
Stack* stack_new(void) { 
    Stack* stack = malloc(sizeof(Stack));

    if (!stack)
        LOG(E_SEGMENTATION_FAULT);

    *stack = (Stack) { 0 };
    return stack;
}
/**
 * stack_destroy:
 * @params: @stack: pointer to stack needed to access properties.
 * 
 * Deallocates given memory from heap to prevent memory leaks.
 * !NOTE - use this when finished with using the stack.
*/
void stack_destroy(Stack* stack) {
    free(stack->_arr);
    stack->_arr = NULL;
    free(stack);
    stack = NULL;
}