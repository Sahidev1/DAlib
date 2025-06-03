#ifndef POINTER_TABLE_H
#define POINTER_TABLE_H

#include <stdint.h>
#include <stddef.h>

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


typedef uint64_t hkey_t;



typedef struct Pointer_table{
    size_t size; //indices available
    uint64_t entries; // total entries
    size_t init_capacity;
    hkey_t (*hash_code) (void* dataptr);
    kv_ptr_pair last_checked;
    kv_ptr_pair** pairs;// array of node entries
} pointer_table;

#define KEYS_ALLOCSIZE(map) (map->entries * sizeof(void*))

int POINTER_TABLE_init(pointer_table *map, const size_t INIT_CAPACITY, hkey_t (*hash_code)(void *key_ptr));

uint64_t POINTER_TABLE_hash_function(hkey_t key_code, size_t size);

int POINTER_TABLE_keys(pointer_table *map, void **keys_set_ptr, size_t keys_set_alloc_size);

int POINTER_TABLE_put(pointer_table *map, void *key_ptr, void *val_ptr);



void *POINTER_TABLE_get(pointer_table *map, void *key_ptr);

int POINTER_TABLE_contains(pointer_table *map, void *key_ptr);

int POINTER_TABLE_delete(pointer_table *map, void *key_ptr);

void POINTER_TABLE_destroy(pointer_table *map);



#ifdef TESTMODE
void printTable(pointer_table* map);
#endif

#endif