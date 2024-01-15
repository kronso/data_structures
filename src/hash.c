#include <stdlib.h>
#include <stdlib.h>

#include "../include/hash.h"
/**
 * hash_new:
 * 
 * Constructs an array of Lists depending on the HASH_CAPACITY.
 * Since the technique for collision resolution being used
 * is seperate chaining, each bucket will contain a List (doubly-linked
 * since I have an implementaton already).
*/
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
/**
 * hash_destroy:
 * @params: @h_table: pointer to the hashtable needed to destroy.
 * 
 * Loops through each node of a bucket and free's the entries.
 * Eventually freeing the list itself, then the hash table.
 * 
 * (I probably need to make an iterator for all so I don't have access
 * to the private props... Idk why this is here)
*/
void hash_destroy(HashTable* h_table) {
    ListNode* node;
    for (size_t i = 0; i < h_table->_capacity; i++) {
        node = h_table->_buckets[i]->_head;
        while (node)
        {
            if (node->_next == NULL) 
            {
                free(node->_val);
                node->_val = NULL;
                free(node);     
                node = h_table->_buckets[i]->_head = NULL;
            }
            else 
            {
                node = node->_next;
                free(node->_prev->_val);
                node->_prev->_val = NULL;
                free(node->_prev);
                node->_prev = NULL;
            }
        }
        free(h_table->_buckets[i]);
        h_table->_buckets[i] = NULL;
    }
    free(h_table->_buckets);
    h_table->_buckets = NULL;
    free(h_table);
    h_table = NULL;
}