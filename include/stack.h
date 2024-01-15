#pragma once
#include <stdio.h>
/**
 * Array implementation of stack data structure.
 * 
 * Pointers allow us to imitate a generic type by casting to... 
 * any datatype but cannot allow the use of integral literals... 
 * (include character literal).
 * Basically anything that doesn't have an address in memory.
 * 
 * If you wan't to assign a value from the stack, you need to...
 * type-cast it first and then dereference it. 
 * 
 * e.g stack_push(&my_stack, my_num);
 *      printf("mynum: %d\n", *(int *) stack_top(stack));
 * 
 * Can get really messy but oh well. :)
*/

/**
 * Stack:
 * @properties: @_arr:  an "array" of addresses
 *              @_size: stores the length of the stack.
*/
typedef struct _Stack {
    void** _arr;
    size_t _size;
} Stack;

/* Modifiers */
void stack_push         (Stack* stack, void* val);
void stack_pop          (Stack* stack);

/* Capacity */
size_t stack_size       (Stack* stack);
unsigned stack_empty    (Stack* stack);

/* Element access */
void* stack_top         (Stack* stack);

/* Construct and destructor */
Stack* stack_new        ();
void stack_destroy      (Stack* stack);