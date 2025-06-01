#ifndef POINTER_TABLE_H
#define POINTER_TABLE_H

#include <stdint.h>

typedef enum  {
    MEM_ALLOCATION_FAILED=1,
    MAP_NO_HASHCODE_FUNCTION,
    MAP_RESIZE_FAILED,
    MAP_KEY_INDEX_OUT_OF_BOUNDS
} error;


typedef struct KV_ptr_pair {
    void* key_ptr;
    void* data_ptr;
    struct KV_ptr_pair* next;
} kv_ptr_pair;


typedef uint32_t hkey_t;



typedef struct Pointer_table{
    uint32_t size; //indices available
    uint32_t entries; // total entries
    uint32_t init_capacity;
    hkey_t (*hash_code) (void* dataptr);
    kv_ptr_pair last_checked;
    kv_ptr_pair** pairs;// array of node entries
} pointer_table;

int POINTER_TABLE_init(pointer_table *map, const uint32_t INIT_CAPACITY, hkey_t (*hash_code)(void *key_ptr));

int POINTER_TABLE_put(pointer_table *map, void *key_ptr, void *val_ptr);
void **POINTER_TABLE_keys(pointer_table *map);


void *POINTER_TABLE_get(pointer_table *map, void *key_ptr);

int POINTER_TABLE_contains(pointer_table *map, void *key_ptr);

int POINTER_TABLE_delete(pointer_table *map, void *key_ptr);

#ifdef TESTMODE
void printTable(pointer_table* map);
#endif

#endif