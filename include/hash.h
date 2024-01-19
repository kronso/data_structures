#pragma once
#include <stdio.h>
#include "list.h"

/**
 * HashTable:
 * @properties: @_buckets:  dynamic array of List pointers      
 *              @_size:     stores the total number of items in each bucket.    
 *              @_capacity: stores the maximum number of elements it can maintain. 
 *
 * Uses the technique seperate chaining to resolve collisions. 
*/
typedef struct _HashTable {
    List**  _buckets;
    size_t _size, _capacity;
} HashTable;

// Initial hash capcaity
#define HASH_CAPACITY 8
// The threshold the ratio of size and capacity musn't exceed.
#define MAX_LOAD_FACTOR 0.75
// The minimum threshold the size of capaity exceeds to decrease its size.
#define MIN_LOAD_FACTOR 0.125
typedef unsigned long long uint_64;

/* Constructor and destructor */
HashTable* hash_new (void);
void hash_destroy   (HashTable* h_table);

/**
 * Including hash.h will implement both,
 * else you can include one or the other.
*/
#include "hash_integral.h"
#include "hash_string.h"
