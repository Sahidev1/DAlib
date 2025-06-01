#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>

typedef enum  {
    MEM_ALLOCATION_FAILED=1,
    MAP_NO_HASHCODE_FUNCTION,
    MAP_RESIZE_FAILED,
    MAP_KEY_INDEX_OUT_OF_BOUNDS
} error;


typedef struct KV_pair {
    void* key_ptr;
    void* data_ptr;
    struct KV_pair* next;
} kv_pair;


typedef uint32_t hkey_t;



typedef struct Hash_table{
    uint32_t size; //indices available
    uint32_t entries; // total entries
    uint32_t init_capacity;
    hkey_t (*hash_code) (void* dataptr);
    kv_pair last_checked;
    kv_pair** pairs;// array of node entries
} hash_table;

int HASH_TABLE_init(hash_table *map, const uint32_t INIT_CAPACITY, hkey_t (*hash_code)(void *key_ptr));

int HASH_TABLE_put(hash_table *map, void *key_ptr, void *val_ptr);
void **HASH_TABLE_keys(hash_table *map);


void *HASH_TABLE_get(hash_table *map, void *key_ptr);

int HASH_TABLE_contains(hash_table *map, void *key_ptr);

int HASH_TABLE_delete(hash_table *map, void *key_ptr);

#ifdef TESTMODE
void printTable(hash_table* map);
#endif

#endif