#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/hash_integral.h"
/**
 * hash_function:
 * @params: @h_table: pointer to the hash table needed to access its props.
 *          @key:     an integral value used to reference its corresponding value in the hash table. 
 * 
 * Uses the Mid-square hash function to get an index within the hash tables capacity.
*/
static uint_64 hash_function(HashTable* h_table, uint_64 key) { 
    return (key * key) % h_table->_capacity;
}
/**
 * hash_int_search:
 * @params: @h_table: pointer to the hash table needed to access its props.
 *          @key:     an integral value used to reference its corresponding value in the hash table.
 * 
 * Traverses the bucket and determines whether a key exists.
 * Returns the key or NULL. 
*/
IntegralEntry* hash_int_search(HashTable* h_table, uint_64 key) { 
    unsigned hash = hash_function(h_table, key);

    List* bucket_hash = h_table->_buckets[hash];
    ListNode* temp = bucket_hash->_head; /* might need something to fix this since _head should be private*/
    // Probably need to replace this with an iterator. 
    // Also I don't know how I can access the private properties of List and ListNode
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
/**
 * hash_int_delete:
 * @params: @h_table: pointer to the hash table needed to modify.
 *          @key:     an integral value used to reference its corresponding value in the hash table.
 * 
 * Traverses the bucket and determines whether a key exists.
 * If found, it is deleted from the bucket else displays that the key did not
 * exist.
*/
void hash_int_delete(HashTable* h_table, uint_64 key) {
    unsigned hash = hash_function(h_table, key);

    List* bucket_hash = h_table->_buckets[hash];
    ListNode* temp = bucket_hash->_head; 
    IntegralEntry* entry;

    int i = 0;
    while (temp != NULL)
    {   
        entry = temp->_val;
        if (entry->_key == key)
        {
            list_erase(bucket_hash, i); 
            h_table->_size--;

            double load_factor = (double) h_table->_size / h_table->_capacity;
            if (load_factor <= MIN_LOAD_FACTOR)
            {
                rehash_int_min(h_table);
            }
            
            return;
        }
        i++;
        temp = temp->_next;
    }
    printf("Key is undefined.\n");
}
/**
 * hash_int_insert:
 * @params: @h_table: pointer to the hash table needed to modify.
 *          @key:     an integral value used to reference its corresponding value in the hash table.
 *          @val:     the corresponding value to a key that is to be stored.
 * 
 * Stores a entry of the new key-value pair. If the user inserts an existing key with a
 * different value, the key's value in the hash_table will be updated to the new one.  
 * If the load factor exceeds the max load factor, we rehash.
*/
void hash_int_insert(HashTable* h_table, uint_64 key, void* val) { 
    unsigned hash = hash_function(h_table, key);

    List* bucket_hash = h_table->_buckets[hash];

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
        rehash_int_max(h_table);
    }
}
/**
 * rehash_int:
 * @params: @h_table: pointer to the hash table needed to modify.
 * 
 * Rehashing involves creating a new array of lists with a doubled capacity,
 * traversing through the previous hash table and hashing the existing keys to the
 * array of new buckets, alongside destroying the previous buckets.
 * This is now the new hash table.
*/
void rehash_int_max(HashTable* h_table) {
    h_table->_capacity *= 2;
    List** new_buckets = malloc(sizeof(List *) * h_table->_capacity);

    for (size_t i = 0; i < h_table->_capacity; i++)
        new_buckets[i] = list_new();

    unsigned hash;
    ListNode* bucket_head;
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
void rehash_int_min(HashTable* h_table) {
    h_table->_capacity /= 2;

    List** new_buckets = malloc(sizeof(List *) * h_table->_capacity);
    for (size_t i = 0; i < h_table->_capacity; i++)
        new_buckets[i] = list_new();

    unsigned hash;
    ListNode* bucket_head;
    IntegralEntry* entry;
    for (size_t j = 0; j < h_table->_capacity * 2; j++) { 
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
