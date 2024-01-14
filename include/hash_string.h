#pragma once

#include "hash.h"

typedef struct _StringEntry {     
    const char *_key;
    void* _value;
} StringEntry;

StringEntry* hash_str_search    (HashTable* h_table, const char* key);
void hash_str_delete            (HashTable* h_table, const char* key);
void hash_str_insert            (HashTable* h_table, const char* key, void* val);

void rehash_str(HashTable* h_table);

