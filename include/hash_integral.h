#pragma once

#include "hash.h"

typedef struct _IntegralEntry { 
    uint_64 _key;   
    void* _value;
} IntegralEntry;

IntegralEntry* hash_int_search  (HashTable* h_table, uint_64 key);
void hash_int_delete    (HashTable* h_table, uint_64 key);
void hash_int_insert    (HashTable* h_table, uint_64 key, void* val);

void rehash_int_max(HashTable* h_table);
void rehash_int_min(HashTable* h_table);
