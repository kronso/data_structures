#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/hash_integral.h"

/* Mid-square hash function for integral keys */
static uint_64 hash_function(HashTable* h_table, uint_64 key) { 
    return (key * key) % h_table->_capacity;
}
IntegralEntry* hash_int_search(HashTable* h_table, uint_64 key) { 
    unsigned hash = hash_function(h_table, key);

    List* bucket_hash = h_table->_buckets[hash];
    Node* temp = bucket_hash->_head; /* might need something to fix this since _head should be private*/
    // Probably need to replace this with an iterator. 
    // Also I don't know how I can access the private properties of List and Node
    IntegralEntry* entry;
    while (temp != NULL)
    {   
        entry = temp->_val;
        if (entry->_key == key)
            return entry;
        
        temp = temp->_next;
    }
    return NULL;
}
void hash_int_delete(HashTable* h_table, uint_64 key) {
    unsigned hash = hash_function(h_table, key);

    List* bucket_hash = h_table->_buckets[hash];
    Node* temp = bucket_hash->_head; 
    IntegralEntry* entry;

    int i = 0;
    while (temp != NULL)
    {   
        entry = temp->_val;
        if (entry->_key == key)
        {
            list_erase(bucket_hash, i); 
            h_table->_size--;
            return;
        }
        i++;
        temp = temp->_next;
    }
    printf("Key is undefined.\n");
}
void hash_int_insert(HashTable* h_table, uint_64 key, void* val) { 
    unsigned hash = hash_function(h_table, key);

    List* bucket_hash = h_table->_buckets[hash];

    /* Update the value if an already existing key is given. */ 
    IntegralEntry* dupe = hash_int_search(h_table, key);
    if (dupe != NULL) {
        dupe->_value = val; 
        return;
    }

    IntegralEntry* new_entry = malloc(sizeof(IntegralEntry));
    *new_entry = (IntegralEntry) { ._key = key, ._value = val };
    list_push_back(bucket_hash, new_entry);

    h_table->_size++;
    
    double load_factor = (double) h_table->_size / h_table->_capacity;
    if (load_factor >= MAX_LOAD_FACTOR) 
    { 
        rehash_int(h_table);
    }
}

void rehash_int(HashTable* h_table) {
    h_table->_capacity *= 2;
    List** new_buckets = malloc(sizeof(List *) * h_table->_capacity);

    for (size_t i = 0; i < h_table->_capacity; i++)
        new_buckets[i] = list_new();

    unsigned hash;
    Node* bucket_head;
    IntegralEntry* entry;
    for (size_t j = 0; j < h_table->_capacity / 2; j++) 
    {
        if (!list_empty(h_table->_buckets[j])) 
        { 
            bucket_head = h_table->_buckets[j]->_head;    

            while (bucket_head != NULL) 
            {
                entry = malloc(sizeof(IntegralEntry));

                *entry = (IntegralEntry) {
                    ._key   = ((IntegralEntry *) bucket_head->_val)->_key,
                    ._value = ((IntegralEntry *) bucket_head->_val)->_value
                };

                hash = hash_function(h_table, entry->_key);
                list_push_back(new_buckets[hash], entry);
                
                bucket_head = bucket_head->_next;
            }
        }
        list_destroy(h_table->_buckets[j]);
    }
    free(h_table->_buckets);
    h_table->_buckets = new_buckets;
}
