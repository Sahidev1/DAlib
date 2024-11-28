
#include "../structures/vector.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){

    if (argc > 1){
        int seed = atoi(argv[2]);
        srand(seed);
    } else {
        srand(time(NULL));
    }

    const int NR_ELEMS = 1127;
    const int ELEM_COUNT = NR_ELEMS / 2;
    int* init_arr = malloc(sizeof(int)*NR_ELEMS);
    for(int i = 0; i < ELEM_COUNT; i++){
        init_arr[i] = rand(); 
    }

    init_array_options opts = {
        .arr_size = NR_ELEMS,
        .array = init_arr,
        .deflate_enable = DEFLATE_ENABLE,
        .elem_count = ELEM_COUNT,
        .elem_size = sizeof(int),
        .inflation = GREEDY,
        .min_arrsize = NR_ELEMS
    };

    vector* v = create_vector_from_array(opts);

    // print all vector data
    printf("inflation policy: %d\n", v->opts.inflation);
    printf("elem_count: %lld\n", get_size(v));
    printf("arr_size: %lld\n", v->arr_size);
    printf("elem_size: %zu\n", v->elem_size);
    printf("deflate_enable: %d\n", v->opts.deflate_enable);
    printf("min_arrsize: %lld\n", v->opts.min_arrsize);
    printf("array: %p\n", v->array);
    printf("inflations: %d\n", v->inflations);

    int opCnt = 34123;
    int maxI = ELEM_COUNT;
    int i = 0;
    int tmp;
    while(i++ < opCnt){
        if(rand()%3 == 0){
            removeIndex(v, rand()%maxI, NULL);
            maxI--;
        }
        else {
            tmp = rand();
            push(v, &tmp);
            maxI++;
        }
    }

    printf("\n\n\n");

    

    printf("inflation policy: %d\n", v->opts.inflation);
    printf("elem_count: %lld\n", get_size(v));
    printf("arr_size: %lld\n", v->arr_size);
    printf("elem_size: %zu\n", v->elem_size);
    printf("deflate_enable: %d\n", v->opts.deflate_enable);
    printf("min_arrsize: %lld\n", v->opts.min_arrsize);
    printf("array: %p\n", v->array);
    printf("inflations: %d\n", v->inflations);

    destroy_vector(v);

    return 0;
}