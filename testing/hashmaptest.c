#include "../structures/hashmap.h"
#include <stdio.h>
#include <string.h>

typedef int mkey;
typedef float mval;

hkey_t hashcode(void* k){
    mkey* mk = k;
    return *mk;
}

int comparator(void* a, void*b){
    mkey* key_a = a; mkey* key_b = b;
    return *key_a - *key_b;
}



int main(){

    hash_map* map = calloc(1,sizeof(hash_map));
    HASH_MAP_init(map, sizeof(mkey), sizeof(mval), &hashcode, &comparator, 1);

    int command = 1;
    int not_first = 0;
    
    mkey* k; mval* v;
    while(command > 0){
        k = calloc(1,sizeof(mkey));
        v = calloc(1,sizeof(mval));
        printf("\naddresses: k:%p, v:%p\n", k, v);
        if(not_first && command == 1){
            printf("\nenter key: ");
            scanf("%d", k);
            printf("\nenter value: ");
            scanf("%f", v);

            HASH_MAP_put(map, k, v);
        }
        if(not_first && command == 2){
            printf("\nEnter key to get:");
            scanf("%d", k);
            mval* res = HASH_MAP_get(map, k);
            if (res == NULL) printf ("\ngot: NULL");
            else printf("\ngot: %f", *res);
        }
        if(not_first && command == 3){
            printf("\n Enter key to contain check:");
            scanf("%d", k);
            if(HASH_MAP_contains(map, k)){
                printf("\ncontains key");
            }            
            else {
                printf("\ndoesnt contain key");
            }
        }

        if(not_first && command == 4){
            printf("\n Enter key to delete: ");
            scanf("%d", k);

            printf("delete status: %d\n", HASH_MAP_delete(map, k));
        }

        printf("\nCommands:\n0) quit\n1) put in kv\n2)get key\n3)contain key check\n4) delete key\n");
        scanf("%d",&command);
        not_first++;
        free(k);
        free(v);
    }
    

    return 0;
}