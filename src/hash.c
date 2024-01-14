#include <stdlib.h>

#include "../include/hash.h"

HashTable* hash_new(void) { 
    HashTable* h_table = malloc(sizeof(HashTable));
    *h_table = (HashTable) { 
        ._buckets = malloc(sizeof(List *) * HASH_CAPACITY),
        ._capacity = HASH_CAPACITY 
        };  // everything else is zero'd

    for (int i = 0; i < HASH_CAPACITY; i++)
        h_table->_buckets[i] = list_new();

    return h_table;
}

void hash_destroy(HashTable* hash) {
    for (size_t i = 0; i < hash->_capacity; i++) {
        list_destroy(hash->_buckets[i]);
    }
    free(hash->_buckets);
    free(hash);
    hash = NULL;
}