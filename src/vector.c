#include <stdlib.h>

#include "../include/vector.h"

void vec_push_back(Vector* vector, void* val) {
    *(vector->_arr + vector->_size++) = val;
    if (vector->_size == vector->_capacity)
    {
        vector->_capacity *= 2;
        vector->_arr = realloc(vector->_arr, sizeof(void *) * vector->_capacity);
    }
}
void vec_pop_back(Vector* vector) {
    //  free(vector->_arr + --vector->_size);
    *(vector->_arr + vector->_size - 1) = NULL;
    vector->_size--;
}
void vec_insert(Vector* vector, void* val, unsigned pos) {
    if (vector->_size + 1 == vector->_capacity)
    {
        vector->_capacity *= 2;
        vector->_arr = realloc(vector->_arr, sizeof(void *) * vector->_capacity);
    }
    for (size_t i = vector->_size; i != pos; i--) {
        *(vector->_arr + i) = *(vector->_arr + i - 1);
    }
    vector->_size++;
    *(vector->_arr + pos) = val;
}
void vec_assign(Vector* vector, void* val, unsigned pos) {
    *(vector->_arr + pos) = val;
}

void vec_erase(Vector* vector, unsigned pos) {

    for (size_t i = pos; i < vector->_size; i++) {
        *(vector->_arr + i) = *(vector->_arr + i + 1);
    }
    vector->_size--;
    *(vector->_arr + vector->_size) = NULL;
}
void vec_clear(Vector* vector) {
    for (size_t i = 0; i < vector->_size; i++) {
        *(vector->_arr + i) = NULL;
    }
}

void* vec_front(Vector* vector) {
    return *(vector->_arr);  
}
void* vec_back(Vector* vector) {
    return *(vector->_arr + vector->_size - 1);
}
void* vec_at(Vector* vector, unsigned pos) {
   return *(vector->_arr + pos); 
}
// idk about this but...
void* vec_data(Vector* vector) {
    return vector->_arr; 
}

size_t vec_size(Vector* vector) {
    return vector->_size;
}
size_t vec_capacity(Vector* vector) {
    return vector->_capacity;  
}
unsigned vec_empty(Vector* vector) {
    return (vector->_size == 0) ? 1: 0;
}

Vector* vec_new(void) {
    Vector* vector = malloc(sizeof(Vector));
    *vector = (Vector) { 
        ._arr      = calloc(INITIAL_CAPACITY, sizeof(void *)),
        ._capacity = INITIAL_CAPACITY
    };
    return vector;
}
void vec_destroy(Vector* vector) {
    free(vector->_arr);
    free(vector);
    vector = NULL;
}
