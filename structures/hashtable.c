#include "hashtable.h"
#include <stdlib.h>
#include <assert.h>

#include <stdio.h>

#if defined TESTMODE
    #define ERROR_CHECK() ({ printf("CHECK line %d\n", __LINE__); });
    #define RESIZE_TRIGGERED(ns,os) (printf("RESIZE TRIGGERED new: %d, old:%d\n", ns, os));
    #define MAX_ENTRIES_PER_INDEX 2
#else
    #define ERROR_CHECK() ;
    #define RESIZE_TRIGGERED(ns,os) ;
    #define MAX_ENTRIES_PER_INDEX 8
#endif

int HASH_TABLE_init(hash_table *map, const uint32_t INIT_CAPACITY, hkey_t (*hash_code)(void *key_ptr))
{
    map->entries = 0;
    map->size = INIT_CAPACITY;
    map->init_capacity = INIT_CAPACITY;
    map->hash_code = hash_code;
    map->pairs = calloc(INIT_CAPACITY, sizeof(kv_pair*));

    if (map->pairs == NULL)
        return MEM_ALLOCATION_FAILED;

    return 0;
}

static uint32_t hash_function(hkey_t key_code, uint32_t size)
{
    return ((key_code ^ (key_code >> 16)) & 0x7fffffff) % size;
}

static uint32_t key_to_hash_index(hash_table* map,void* key_ptr, uint32_t size){
    hkey_t hash = map->hash_code(key_ptr);
    return hash_function(hash, size);
}


static int get_kv_pairs(hash_table *map, kv_pair** ptr, size_t ptr_alloc_size){
    if (map->entries * sizeof(kv_pair*) > ptr_alloc_size) return 1;

    int i = 0; int j = 0;

    while(i < map->size){
        kv_pair *tmp = map->pairs[i++];
        while(tmp != NULL){
            ptr[j++] = tmp;
            tmp = tmp->next;
        }
    }

    return 0;
}

void **HASH_TABLE_keys(hash_table *map)
{
    void **keys_set_ptr = calloc(map->entries, sizeof(void *));

    int i = 0;
    int j = 0;

    while (i < map->size)
    {
        kv_pair *pairs = map->pairs[i++];
        while (pairs != NULL)
        {
            *(keys_set_ptr+j) = pairs->key_ptr;
            j++;
            pairs = pairs->next;
        }
    }

    return keys_set_ptr;
}

static int put(uint32_t index, kv_pair** pairs, uint32_t map_size, kv_pair* new_pair)
{
    if (index >= map_size)
        return MAP_KEY_INDEX_OUT_OF_BOUNDS;

    kv_pair *pair = pairs[index];
    kv_pair *prev = pair;
    while (pair != NULL)
    {
        prev = pair;
        pair = pair->next;
    }

    ERROR_CHECK();

    if (prev == NULL)
    {
        pairs[index] = new_pair;
    }
    else
    {
        prev->next = new_pair;
    }

    if (new_pair == NULL)
        return MEM_ALLOCATION_FAILED;

    ERROR_CHECK();


    return 0;
}

static int delete(uint32_t index, kv_pair** pairs, void *key_ptr, uint32_t size)
{
    if (index >= size)
        return MAP_KEY_INDEX_OUT_OF_BOUNDS;

    kv_pair *pair = pairs[index];
    kv_pair *prev = NULL;

    while (pair != NULL)
    {
        if (pair->key_ptr == key_ptr)
        {
            if (prev == NULL)
            {
                pairs[index] = pair->next;
            }
            else
            {
                prev->next = pair->next;
            }
            free(pair);
            break;
        }

        prev = pair;
        pair = pair->next;
    }
    return 0;
}


/**
 * map points to hash_table, new_size is the new number of array indices
 */
static int resize(hash_table *map, uint32_t new_size)
{
    RESIZE_TRIGGERED(new_size, map->size);
    ERROR_CHECK();
    // map->pairs = realloc(map->pairs, new_size * sizeof(kv_pair));
    kv_pair **pairs = calloc(new_size, sizeof(kv_pair*));

    ERROR_CHECK();
    if (pairs == NULL)
        return MEM_ALLOCATION_FAILED;
    ERROR_CHECK();
    /*if (new_size > map->size){
        uint32_t i = map->size;
        while (i < new_size){
            map->pairs[i++] = NULL;
        }
    }*/

    map->last_checked.key_ptr = NULL;
    kv_pair** kv_set = calloc(map->entries, sizeof(kv_pair*));
    get_kv_pairs(map, kv_set, map->entries * sizeof(kv_pair*));


    ERROR_CHECK();

    void *valptr;
    uint32_t hashindex;
    for (int i = 0; i < map->entries; i++)
    {
        //hashindex = key_to_hash_index(map, kv_set[i]->key_ptr, map->size);
        //delete(hashindex, map->pairs, key_set[i], map->size);
        hashindex = key_to_hash_index(map, kv_set[i]->key_ptr, new_size);
        kv_set[i]->next = NULL;
        if (put(hashindex, pairs, new_size, kv_set[i]) != 0) return MAP_RESIZE_FAILED;
    }

    ERROR_CHECK();


    map->size = new_size;

    free(map->pairs);
    free(kv_set);
    map->pairs = pairs;

    ERROR_CHECK();
    return 0;
}



int HASH_TABLE_put(hash_table *map, void *key_ptr, void *val_ptr)
{
    if (map->hash_code == NULL)
        return MAP_NO_HASHCODE_FUNCTION;
    ERROR_CHECK();
    if (map->entries >= map->size * MAX_ENTRIES_PER_INDEX)
    {
        
        if (resize(map, 2 * map->size) != 0)
            return MAP_RESIZE_FAILED;
    

    }

    ERROR_CHECK();

    hkey_t hash = map->hash_code(key_ptr);
    uint32_t index = hash_function(hash, map->size);

    ERROR_CHECK();

    kv_pair* new_pair = calloc(1, sizeof(kv_pair));
    int retVal = put(index, map->pairs, map->size, new_pair);
    ERROR_CHECK();
    if (retVal != 0){
        free(new_pair);
        return retVal;
    }

    new_pair->key_ptr = key_ptr;
    new_pair->data_ptr = val_ptr;
    map->entries++;

    ERROR_CHECK();

    return 0;
}

void *HASH_TABLE_get(hash_table *map, void *key_ptr)
{

    /* check last check field, its keep last contain checked key */
    void *tmp = map->last_checked.key_ptr;
    map->last_checked.key_ptr = NULL;

    ERROR_CHECK();

    if (tmp != NULL && tmp == key_ptr)
        return map->last_checked.data_ptr;

    ERROR_CHECK();

    hkey_t hash = map->hash_code(key_ptr);
    uint32_t index = hash_function(hash, map->size);

    if (index >= map->size)
        return NULL;

    kv_pair *pair = map->pairs[index];

    while (pair != NULL)
    {
        if (pair->key_ptr == key_ptr)
            return pair->data_ptr;
        pair = pair->next;
    }

    ERROR_CHECK();

    return NULL;
}

// check if hash_table map contains key
int HASH_TABLE_contains(hash_table *map, void *key_ptr)
{
    void *val_ptr = HASH_TABLE_get(map, key_ptr);
    // save in last checked field
    map->last_checked.key_ptr = key_ptr;
    map->last_checked.data_ptr = val_ptr;
    return val_ptr != NULL;
}

int HASH_TABLE_delete(hash_table *map, void *key_ptr)
{
    map->last_checked.key_ptr = NULL;

    hkey_t hash = map->hash_code(key_ptr);
    uint32_t index = hash_function(hash, map->size);

    int retVal = delete(index, map->pairs, key_ptr, map->size);
    if (retVal != 0)
        return retVal;

    map->entries--;

    if(map->size > map->init_capacity && map->entries < map->size / 2){
        if (resize(map, map->size / 2) != 0) return MAP_RESIZE_FAILED;

    }

    return 0;
}


/*                        TESTING                            */


void printTable(hash_table* map){
    printf("\n");
    printf("--PRINTING HASHTABLE--\n");
    printf("\tSIZE: %d\n\tENTRIES: %d\n", map->size, map->entries);
    printf("\tLAST_CHECKED: key: %p, val: %p\n", map->last_checked.key_ptr, map->last_checked.data_ptr);
    printf("\t--PRINTING_KVPAIRS--\n");
    
    for(int i = 0; i < map->size; i++){
        kv_pair* p = map->pairs[i];
        
        printf("\tHash index %d keys:\n", i);
        
        if(p == NULL) printf("\t\tEMPTY\n");
        else{
            while(p != NULL){
                printf("\t\t Key_ptr: %p, Val_ptr: %p\n", p->key_ptr, p->data_ptr);
                p = p->next;
            }
        }
        
    }
    printf("\t--END KV_PAIR PRINT--\n");
    printf("--END HASH TABLE PRINT---\n");
    printf("\n");
}