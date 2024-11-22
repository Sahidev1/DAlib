#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vector.h"

#define DEFAULT_MIN_ELEMS 4
#define DEFAULT_DEFLATE_MODE (DEFLATE_ENABLE)
#define DEFAULT_INIT_ELEMCOUNT 4
#define DEFAULT_FLATION (GREEDY)


int get_arr_memsize(vector* v){
    int inflations = v->inflations;
    int init_arrsize = v->opts.init_arrsize;
    int memsize;
    if(v->opts.inflation == GREEDY){
        memsize = init_arrsize * (1<<inflations);
    } 
    if(v->opts.inflation == CONSERVATIVE){
        memsize = init_arrsize * (((int) pow(3,inflations))/(1<<inflations)); 
    }
    return memsize;
}

vector* create_vector(int elem_size, vector_options* opts){
    vector* vect = malloc(sizeof(vector));
    vector_options* opt_ptr = &vect->opts;
    if (opts == NULL){
        opt_ptr->deflate_enable = DEFAULT_DEFLATE_MODE;
        opt_ptr->deflation = DEFAULT_FLATION;
        opt_ptr->inflation = DEFAULT_FLATION;
        opt_ptr->init_arrsize = DEFAULT_INIT_ELEMCOUNT;
        opt_ptr->min_elems = DEFAULT_MIN_ELEMS;
    }
    memcpy(opt_ptr, opts, sizeof(vector_options));
    vect->elem_count = 0;
    vect->elem_size = elem_size;
    vect->inflations = 0;
    vect->array = malloc(elem_size * opt_ptr->init_arrsize);

    return vect;
}

int destroy_vector(vector* v){
    free(v->array);
    free(v);
    return 0;
}
