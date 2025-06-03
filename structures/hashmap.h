#ifndef HASHMAP_H
#define HASHMAP_H

#include "pointer_table.h"
#include <stdlib.h>
#include <string.h>

typedef struct Hashmap
{
    pointer_table *internal;
    size_t key_size;
    size_t value_size;
    hkey_t (*hash_code) (void* key_ptr);
    int (*comparator) (void* a, void*b);
} hash_map;




int HASH_MAP_init(hash_map *map, size_t keysize, size_t valuesize, hkey_t (*hashcode)(void *keyptr), int (*comparator)(void *a, void *b), int init_capacity);

int HASH_MAP_put(hash_map *map, void *key_ptr, void *val_ptr);

void *HASH_MAP_get(hash_map *map, void *key_ptr);

int HASH_MAP_contains(hash_map *map, void *key_ptr);

int HASH_MAP_delete(hash_map *map, void *key_ptr);

void HASH_MAP_destroy(hash_map *map);




#define HASHMAP_PUT(map, k, v) ({\
    void* key = malloc(map->key_size);\
    void* value = malloc(map->value_size);\
    memcpy(key, &k, map->key_size);\
    memcpy(value, &v, map->value_size);\
    POINTER_TABLE_put(map->internal, key, value);\
})\


#define HASHMAP_GET(map, k, v_ptr) ({ \
    hkey_t code = map->hash_code(&k);\
    hkey_t index = POINTER_TABLE_hash_function(code, map->internal->size);\
    kv_ptr_pair* pair = map->internal->pairs[index];\
    v_ptr = NULL;\
    while(pair != NULL){ \
        if (map->comparator(&k, pair->key_ptr) == 0){ vptr = pair->data_ptr; break;}; \
        pair = pair.next \
    } \
})\


#endif