#include "../structures/node_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* fun(void * v, long long index){
    int* a = v;
    printf("index: %lld, value: %d\n", index, *a);
}


int main(int argc, char** argv){

    if (argc > 1){
        int seed = atoi(argv[2]);
        srand(seed);
    } else {
        srand(time(NULL));
    }
    

    node_list* l = create_nodelist(sizeof(int));

    const int NR_ELEMS = 1000;
    int tmp;
    for (int i = 0; i < NR_ELEMS; i++){
        tmp = rand() % 1000;
        push(l, &tmp);
    }
    
    traverse_list(l, fun);
    printf("adds done\n");


    int elemsCnt = NR_ELEMS;

    int opCount = NR_ELEMS * 50;
    int i = 0;
    while(i++ < opCount){
        if(rand()%2 == 0){
            tmp = rand();
            push(l, &tmp);
            elemsCnt++;
        } else {
            removeIndex(l,rand()%elemsCnt--, NULL);
        }
    }
    /*for (int i = 0; i < NR_ELEMS - 50; i++){
        removeIndex(l, rand()%elemsCnt--, NULL);
    }*/

    printf("\n\n\n");
    traverse_list(l, fun);

    destoy_nodelist(l);

    return 0;
} 