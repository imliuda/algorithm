#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdbool.h>

typedef int HashFunc(void *key);
typedef bool HashEqualFunc(void *key1, void *key2);

typedef struct hash_bucket hash_bucket;
struct hash_bucket {
    void        *key;
    void        *value;
    hash_bucket *next;
};

typedef struct hash_table {
    list    **buckets;
    int     table_size;
    int     cur_size;
    float   fmax;
    float   fmin;
} hash_table;

HashFunc string_hash(void *key);
HashEqualFunc string_equal(void *key1, void *key2);

hash_table *hash_table_new(HashFunc hash, HashEqualFunc equal);
void hash_table_set(hash_table *table, void *key, void *value);
bool hash_table_isset(hash_table *table, void *key);
void hash_table_unset(hash_table *table, void *key);
void *hash_table_get(hash_table *table, void *key);

#endif
