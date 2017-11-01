#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hash_table.h"

/* https://en.wikipedia.org/wiki/PJW_hash_function */
HashFunc string_hash(void *key) {
    unsigned int h = 0, high;
    while (*key) {
        h = ( h << 4 ) + *key++;
        if ( high = h & 0xF0000000 )
            h ^= high >> 24;
        h &= ~high;
    }
    return h;
}

HashEqualFunc string_equal(void *key1, void *key2) {
    return strcmp(key1, key2) == 0 ? true : false;
}

hash_table *hash_table_new(HashFunc hash, HashEqualFunc equal) {
    hash_table *t = malloc(sizeof(hash_table));
    // default table size 128
    t->buckets = calloc(128, sizeof(void *));
    t->fmax = 0.75;
    t->fmin = 0.375;
    t->table_size = 128;
    t->cur_size = 0;
    t->hash = hash;
    t->equal = equal;
    return t;
}

void *hash_table_set(hash_table *table, void *key, void *value) {
    h = table->hash(key);
    p = h % table->size;
    hash_bucket *b = table->buckets[p];
    
    if (table->buckets[p]) {
        table->buckets[p]->append(value);
    } else {
        table->buckets[p] = malloc(sizeof(hash_bucket));
        table->buckets[p]->next 
    }
}
