#include "hashmap.h"



static uint64_t pointer_table_index(pointer_table* pt, void* key_ptr){
    uint64_t hash = pt->hash_code(key_ptr);
    uint64_t index = POINTER_TABLE_hash_function(hash, pt->size);
    return index;
}

static kv_ptr_pair* find_matching_kv_ptr_pair(hash_map* map, void* key_ptr){
    uint64_t index = pointer_table_index(map->internal, key_ptr);
    kv_ptr_pair* p = map->internal->pairs[index];

    while(p != NULL){
        if(map->comparator(key_ptr, p->key_ptr) == 0) return p;
        p = p->next;
    }

    return NULL;
}

int HASH_MAP_init(hash_map* map, size_t keysize, size_t valuesize, hkey_t (*hashcode) (void *keyptr), int (*comparator) (void* a, void* b) ,int init_capacity){
    map->key_size =keysize;
    map->value_size= valuesize;
    map->hash_code = hashcode;
    map->comparator = comparator;
    map->internal = calloc(1, sizeof(pointer_table));
    
    POINTER_TABLE_init(map->internal, init_capacity, map->hash_code);
}

int HASH_MAP_put(hash_map* map, void* key_ptr, void* val_ptr){
    kv_ptr_pair* p = find_matching_kv_ptr_pair(map, key_ptr);
    if (p != NULL){
        memcpy(p->data_ptr, val_ptr, map->value_size);
        return 0;
    }

    void* heap_key = malloc(map->key_size);
    void* heap_val = malloc(map->value_size);
    memcpy(heap_key, key_ptr, map->key_size);
    memcpy(heap_val, val_ptr, map->value_size);

    return POINTER_TABLE_put(map->internal, heap_key, heap_val);
}

void* HASH_MAP_get(hash_map* map, void* key_ptr){
    
    kv_ptr_pair* p = find_matching_kv_ptr_pair(map, key_ptr);
    if (p == NULL) return NULL;

    return p->data_ptr;
}

int HASH_MAP_contains(hash_map* map, void* key_ptr){
    return HASH_MAP_get(map, key_ptr) != NULL;
}

int HASH_MAP_delete(hash_map* map, void* key_ptr){
    kv_ptr_pair* p = find_matching_kv_ptr_pair(map, key_ptr);
    if (p == NULL) return 0;
    void* kref = p->key_ptr;
    void* vref = p->data_ptr;
    int ret_val = POINTER_TABLE_delete(map->internal, kref);
    free(kref);
    free(vref);

    return ret_val;
}

void HASH_MAP_destroy(hash_map* map){
    size_t key_alloc_size = KEYS_ALLOCSIZE(map->internal);
    void** keys = malloc(key_alloc_size);
    int ret_val = POINTER_TABLE_keys(map->internal, keys, key_alloc_size);
    int i = 0;
    while(i < map->internal->entries){
        void* val = POINTER_TABLE_get(map->internal, keys[i]);
        free(val);
        free(keys[i]);
        i++;
    }

    POINTER_TABLE_destroy(map->internal);
    free(map->internal);
    free(keys);
}