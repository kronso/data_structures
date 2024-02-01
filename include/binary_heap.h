#pragma once
#include <stdio.h>

#define INITIAL_CAPACITY 10

typedef struct _Heap {
    int* _arr;
    size_t _size, _cap;
} Heap;

void heap_insert    (Heap* _heap, int _val);
void heap_delete    (Heap* _heap); // Deletes root node and maintains completeness of binary tree

void heap_create    (Heap* _heap, int* _arr, size_t _size);
void heapify        (int* _arr, size_t _size);

void* heap_max      (Heap* _heap);
size_t heap_size    (Heap* _heap);
unsigned heap_empty (Heap* _heap);

void heap_print     (Heap* _heap); // temp
                                   //
Heap* heap_new(void);
void heap_destroy(Heap* _heap);
