#include "../structures/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* fun(void * v, int index){
    int* a = v;
    printf("index: %d, value: %d\n", index, *a);
}


int main(int argc, char** argv){

    if (argc > 1){
        int seed = atoi(argv[2]);
        srand(seed);
    } else {
        srand(time(NULL));
    }
    

    vector* v = create_vector(sizeof(int), NULL);


    printf("created\n");

    
    const int NR_ELEMS = 1000;
    int tmp;
    for (int i = 0; i < NR_ELEMS; i++){
        tmp = rand() % 1000;
        push(v, &tmp);
    }
    
    
    traverse_list(v, fun);
    printf("adds done\n");


    int elemsCnt = NR_ELEMS;

    int opCount = (NR_ELEMS) * 50;
    int i = 0;
    int rem = 0;
    while(i++ < opCount){
        if(rand()%2 == 0){
            tmp = rand();
            push(v, &tmp);
            elemsCnt++;
        } else {

            rem = elemsCnt <= 0? elemsCnt: rand()%(elemsCnt--);
            printf("index: %d, elemsCnt: %d, rem: %d, arrsize: %d\n",i, v->elem_count, rem, v->arr_size);
            removeIndex(v,rem, NULL);
        }
    }
    /*for (int i = 0; i < NR_ELEMS - 50; i++){
        removeIndex(l, rand()%elemsCnt--, NULL);
    }*/

   
    printf("\n\n\n");
    traverse_list(v, fun);

    destroy_vector(v); 
    

    return 0;
} 