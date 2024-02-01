#pragma once

#include <stdio.h>

typedef struct _Vector {
    void** _arr;
    size_t _size, _capacity;
} Vector;

#define INITIAL_CAPACITY 10

void vec_push_back  (Vector* vector, void* val);
void vec_pop_back   (Vector* vector);
void vec_insert     (Vector* vector, void* val, unsigned pos);
void vec_assign     (Vector* vector, void* val, unsigned pos);
void vec_erase      (Vector* vector, unsigned pos);
void vec_clear      (Vector* vector);

void* vec_front     (Vector* vector);
void* vec_back      (Vector* vector);
void* vec_at        (Vector* vector, unsigned pos);
void* vec_data      (Vector* vector);

size_t vec_size     (Vector* vector);
size_t vec_capacity (Vector* vector);
unsigned vec_empty  (Vector* vector);

Vector* vec_new     (void);
void vec_destroy    (Vector* vector);
