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
    
    vector_options opts = {.deflate_enable = DEFLATE_ENABLE, .init_arrsize = 8, .min_arrsize = 8, .inflation = CONSERVATIVE };
    vector* v = create_vector(sizeof(int), &opts);


    printf("created\n");

    //print all vector data
    printf("inflation policy: %d\n", v->opts.inflation);
    
    const int NR_ELEMS = 36411;
    int tmp;
    for (int i = 0; i < NR_ELEMS; i++){
        tmp = rand() % 1000;
        push(v, &tmp);
    }

    //remove 10k elements
    int elemsCnt = NR_ELEMS;
    for (int i = 0; i < 35751; i++){
        removeIndex(v,rand()%elemsCnt--, NULL);
    }
    
    
   // traverse_list(v, fun);
    printf("adds done\n");



    int opCount = (NR_ELEMS) * 2;
    int i = 0;
    int rem = 0;
    while(i++ < opCount){
        if(rand()%2 == 0){
            tmp = rand();
            push(v, &tmp);
            elemsCnt++;
        } else {

            rem = elemsCnt <= 0? elemsCnt: rand()%(elemsCnt--);
            //printf("index: %d, elemsCnt: %d, rem: %d, arrsize: %d\n",i, v->elem_count, rem, v->arr_size);
            removeIndex(v,rem, NULL);
        }
    }
    /*for (int i = 0; i < NR_ELEMS - 50; i++){
        removeIndex(l, rand()%elemsCnt--, NULL);
    }*/

   
    printf("\n\n\n");
    //traverse_list(v, fun);

    printf("inflations: %d, arrsize: %lld  \n", v->inflations,v->arr_size);

    destroy_vector(v); 
    


    return 0;
} 