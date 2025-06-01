#include "../structures/hashtable.h"
#include <stdio.h>

#define INIT_CAPACITY 1


typedef struct {
    int X, Y;
} Key;

typedef struct {
    char* descriptor;
} Value;

hkey_t hashcode(void* key){
    Key* data = key;
    return data->X ^ data->Y;
}

void printmap(hash_table* map){
    printf("Map addr: %p\n", map);

    printf("Entries: %d\n", map->entries);
    printf("Size: %d\n", map->size);

}

int main(){
    
    hash_table map;

    HASH_TABLE_init(&map, INIT_CAPACITY, &hashcode);



    Key k = {.X = 22, .Y = 224};
    Value v = {.descriptor="cat location"};
    Key k0 = {.X = 222, .Y = 214};
    Value v0 = {.descriptor="dog location"};
    Key k1 = {.X = 3, .Y = 4};
    Value v1 = {.descriptor="box location"};
    HASH_TABLE_put(&map, &k, &v);
    HASH_TABLE_put(&map, &k0, &v0);
    printTable(&map);
    

    printf("resize: %d\n",HASH_TABLE_put(&map, &k1, &v1));
    printmap(&map);
    printTable(&map);

    Value* hv = HASH_TABLE_get(&map, &k);
    printf("val PTR: %p, %p\n", &v, hv );
    printf("VALUE: %s\n", hv->descriptor);

    printTable(&map);

    int contains = HASH_TABLE_contains(&map, &k1);
    printf("contains: %s\n", contains == 0?"false":"true");
    
    printf("delete: %d\n",HASH_TABLE_delete(&map, &k1));
    contains = HASH_TABLE_contains(&map, &k1);
    printf("contains: %s\n", contains == 0?"false":"true");
    printf("delete: %d\n",HASH_TABLE_delete(&map, &k1));
    printTable(&map);


    return 0;
}