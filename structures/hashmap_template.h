#ifndef HASHMAP_TEMPLATE_H
#define HASHMAP_TEMPLATE_H

#include "hashmap.h"

/*#ifndef K
#error "You must define K (key type) before including hashmap_template.h"
#endif

#ifndef V
#error "You must define V (value type) before including hashmap_template.h"
#endif

#include "hashmap.h"

// Macro to compute key and value sizes
#define KSIZE sizeof(K)
#define VSIZE sizeof(V)

// Macro to initialize the map
#define MAP_INIT(map, hf, cf, i) \
    HASH_MAP_init(map, KSIZE, VSIZE, (hf), (cf), i)
*/
#define FUN_GEN(K,V, name) (MAP_##K##_##V##_##name)

/**
 * int HASH_MAP_init(hash_map *map, size_t keysize, size_t valuesize, 
 * hkey_t (*hashcode)(void *keyptr), int (*comparator)(void *a, void *b),
 *  int init_capacity)
 */

// Macro to generate function definitions for key/value pair
#define DEFINE_HASHMAP_FOR(K, V) \
    static inline int FUN_GEN(K, V, INIT)(hash_map* map, hkey_t (*hashcode)(void* keyptr), int (*comparator)(void*a,void*b), int capacity){\
        return HASH_MAP_init(map, sizeof(K), sizeof(V), hashcode, comparator, capacity);\
    }\
    static inline int FUN_GEN(K, V, PUT)(hash_map* map, K key, V val) { \
        return HASH_MAP_put(map, &key, &val); \
    }\
    static inline V* FUN_GEN(K, V, GET)(hash_map* map, K key){\
        return HASH_MAP_get(map, &key);\
    }\

#endif // HASHMAP_TEMPLATE_H
