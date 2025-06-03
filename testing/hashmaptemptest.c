#include <stdio.h>
#include "../structures/hashmap.h"

#define K int
#define V float
#include "../structures/hashmap_template.h"

DEFINE_HASHMAP_FOR(int, float);

static hkey_t hashcode( void* key){
    int* k = key;
    return *k;
}

static int comparator(void* a, void* b){
    int* ka = a; int* kb = b;
    return *ka - *kb;
}




int main(){



    hash_map m;
    hash_map* map = &m;

    //MAP_INIT(map, &hashcode, &comparator, 1);
    //HASH_MAP_init(map, sizeof(int), sizeof(float), &hashcode, &comparator, 1);
    MAP_int_float_INIT(map, &hashcode, &comparator, 1);
    MAP_int_float_PUT(map, 23, 3.44);
    MAP_int_float_PUT(map, 55, 3.111);

    float* fptr = MAP_int_float_GET(map, 23);
    printf("float: %f\n", *fptr);


    return 0;
}