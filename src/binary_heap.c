#include <stdlib.h> 

#include "../include/binary_heap.h"

int _parent(int* _arr, int pos)
{
    int parent_idx = (pos - 1) / 2; 
    return *(_arr + parent_idx);
}
void _swap(int* _arr, int i, int j)
{
    int temp = _arr[i];
    _arr[i] = _arr[j];
    _arr[j] = temp;
}

unsigned heap_empty(Heap* _heap)
{
    return (_heap->_size == 0) ? 1: 0;
}
size_t heap_size(Heap* _heap) 
{
    return _heap->_size;
}

void heap_insert(Heap* _heap, int _val)
{
    if (_heap->_size == _heap->_cap)
    {
        _heap->_cap *= 2;
        _heap->_arr = realloc(_heap->_arr, sizeof(int) * _heap->_cap);
    }
    *(_heap->_arr + _heap->_size) = _val;
    _heap->_size++;
    if (_heap->_size == 1) return;

    int end_idx = _heap->_size - 1;
    int parent_idx = (end_idx - 1) / 2;
    while (_heap->_arr[end_idx] > _heap->_arr[parent_idx] && end_idx != -1)
    {
        _swap(_heap->_arr, end_idx, parent_idx);
        end_idx    = parent_idx;
        parent_idx = (end_idx - 1) / 2;
    }
}
void heap_delete(Heap* _heap)
{
    if (heap_empty(_heap)) return;

    _swap(_heap->_arr, 0, _heap->_size - 1);
    _heap->_size--;
    
    int i = 0;
    int left_idx  = i * 2 + 1;
    int right_idx = i * 2 + 2;
    int largest_idx = (_heap->_arr[left_idx] > _heap->_arr[right_idx]) ? left_idx: right_idx;
    
    while ((_heap->_arr[i] < _heap->_arr[largest_idx]) && right_idx < _heap->_size)
    {
        _swap(_heap->_arr, i, largest_idx);
        i = largest_idx;
        left_idx  = i * 2 + 1;
        right_idx = i * 2 + 2;
        largest_idx = (_heap->_arr[left_idx] > _heap->_arr[right_idx]) ? left_idx: right_idx;
    }
    if (left_idx < _heap->_size)
    {
        if (_heap->_arr[i] < _heap->_arr[left_idx])
            _swap(_heap->_arr, i, left_idx);
    }


}
void heapify(int* _arr, size_t _size)
{
    if (!_arr) return;

    int largest_idx, left_idx, right_idx;
    for (int i = _size; i != -1; --i)
    {
        left_idx  = i * 2 + 1;
        right_idx = i * 2 + 2; 
        if (right_idx < _size)
        {
            largest_idx = -1;

            if (_arr[left_idx] > _arr[right_idx])
                largest_idx = left_idx;
            else if (_arr[right_idx] > _arr[left_idx])
                largest_idx = right_idx;

            if (largest_idx != -1)
            {
                int it = i;
                while (_arr[it] < _arr[largest_idx])
                {
                    _swap(_arr, it, largest_idx);
                    it = largest_idx;
                    left_idx = it * 2 + 1;
                    right_idx = it * 2 + 2;

                    largest_idx = -1;
                    if (right_idx < _size)
                        largest_idx = (_arr[left_idx] > _arr[right_idx]) ? left_idx: right_idx;
                    else if (left_idx < _size)
                        largest_idx = left_idx;
                }
            }   
        }
        else if (left_idx < _size)
        {
            if (_arr[i] < _arr[left_idx])
                _swap(_arr, i, left_idx);
        }
    }
}
void heap_print(Heap* _heap)
{
    for (size_t i = 0; i < _heap->_size; i++)
        printf("%d ", _heap->_arr[i]);
    printf("\n");
}
Heap* heap_new(void) 
{
    Heap* new_heap = malloc(sizeof(Heap));
    *new_heap  = (Heap) {
        ._arr  = malloc(sizeof(int) * INITIAL_CAPACITY),
        ._cap  = INITIAL_CAPACITY
    }; 
    return new_heap;
}
void heap_destroy(Heap* _heap) {
    free(_heap->_arr);
    _heap->_arr = NULL;
    free(_heap);
    _heap = NULL;
}
