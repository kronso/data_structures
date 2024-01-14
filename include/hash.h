#pragma once
#include <stdio.h>
#include "list.h"

typedef struct _HashTable {
    List**  _buckets;
    size_t _size, _capacity;
} HashTable;

#define HASH_CAPACITY 8
/** 
 * With separate chaining, the value of α max that gives 
 * best performance is typically between 1 and 3. 
*/
#define MAX_LOAD_FACTOR 0.75

typedef unsigned long long uint_64;

HashTable* hash_new (void);
void hash_destroy   (HashTable* h_table);

#include "hash_integral.h"
#include "hash_string.h"