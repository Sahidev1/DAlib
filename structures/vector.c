#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "vector.h"

#define DEFAULT_MIN_ELEMS 4
#define DEFAULT_DEFLATE_MODE (DEFLATE_ENABLE)
#define DEFAULT_INIT_ELEMCOUNT 4
#define DEFAULT_FLATION (GREEDY)



/*
    * Calculate the size of the array based on the inflation strategy
    * @param base: the initial size of the array
    * @param n: the number of inflations
    * @param f: the inflation strategy
    * @return the size of the array
*/
int calculate_arr_size(int base, int n, inflation f){
    if (f == GREEDY){
        return base*(1<<n);
    }
    printf("n: %d\n", n);
    if (f == CONSERVATIVE){
        return base * (((int) pow(3, n))/(1<<n));
    }
}

/*
    * Deflate the array
    * @param v: the vector to deflate
    * @return 0 if the deflation was successful, NULL_VECTOR if the vector is NULL
*/
int deflate(vector* v){
    if(v == NULL) return NULL_VECTOR;
    if(v->arr_size <= v->opts.min_elems || v->inflations == 0) return 0;
    v->inflations--;
    v->arr_size = calculate_arr_size(v->opts.init_arrsize, v->inflations, v->opts.inflation);
    v->array = realloc(v->array, v->arr_size*v->elem_size);
    if (v->array == NULL) {
        printf("realloc failed\n");
        exit(3);
    }
}

/*
    * Inflate the array
    * @param v: the vector to inflate
    * @return 0 if the inflation was successful, NULL_VECTOR if the vector is NULL
*/
int inflate(vector *v){
    if(v == NULL) return NULL_VECTOR;
    v->inflations++;
    v->arr_size = calculate_arr_size(v->opts.init_arrsize, v->inflations, v->opts.inflation);
    v->array = realloc(v->array, v->arr_size*v->elem_size);
    return 0;
}

/*
    * Shift the elements of the array to the right
    * @param v: the vector to shift
    * @param from: the index to start shifting from
    * @param to: the index to shift to
    * @return 0 if the shift was successful, NULL_VECTOR if the vector is NULL
*/
int shift_elems_right(vector* v, int from, int to){
    if (v == NULL) return NULL_VECTOR;

    int i = to;
    void* arr = v->array;
    int esz = v->elem_size;
    while(i > from){
        memcpy((char*) arr + (i * esz), (char*)arr + ((i - 1) * esz), esz);
        i--;
    }

    return 0;
}

/*
    * Shift the elements of the array to the left
    * @param v: the vector to shift
    * @param from: the index to start shifting from
    * @param to: the index to shift to
    * @return 0 if the shift was successful, NULL_VECTOR if the vector is NULL
*/
int shift_elems_left(vector *v, int from, int to){
    if (v == NULL) return NULL_VECTOR;

    int i = from; 
    void* arr = v->array;
    int esz = v->elem_size;

    while(i < to){
        memcpy((char*)arr + (i * esz), (char*)arr + ((i+1) *esz), esz);
        i++;
    }

    return 0;
}


/* add an element to the vector
    * @param v: the vector to add to
    * @param E: the element to add
    * @param index: the index to add the element to
    * @return 0 if the element was added successfully, NULL_VECTOR if the vector is NULL, INDEX_OUT_BOUND if the index is out of bounds
*/
int add(vector* v, void* E, int index){
    if(v == NULL) return NULL_VECTOR;
    if(index > v->elem_count || index < 0) return INDEX_OUT_BOUND;
    if (v->elem_count >= v->arr_size){
        inflate(v);
    }


    if (index == v->elem_count){
        memcpy(((char*)v->array + (v->elem_size*index)), E, v->elem_size);
    } else {
        shift_elems_right(v, index, v->elem_count);
        memcpy((char*)v->array + (v->elem_size * index), E, v->elem_size);
    }

    v->elem_count++;
    return 0;
}

int push(vector* v, void* E){
    return add(v, E, v->elem_count);
}

/* remove an element from the vector
    * @param v: the vector to remove from
    * @param index: the index to remove the element from
    * @param ret_E: the element to remove
    * @return 0 if the element was removed successfully, NULL_VECTOR if the vector is NULL, INDEX_OUT_BOUND if the index is out of bounds
*/
int removeIndex(vector* v, int index, void* ret_E){
    if(v == NULL) return 1;
    if(index >= v->elem_count || index < 0) return 1;
    
    if (ret_E != NULL){
        memcpy(ret_E, (char*)v->array + (v->elem_size* index), v->elem_size);
    }

    if(index != v->elem_count - 1){
        shift_elems_left(v, index, v->elem_count - 1);
    }
    v->elem_count--;

    if(v->opts.deflate_enable == DEFLATE_ENABLE && v->arr_size > v->opts.init_arrsize && v->elem_count < v->arr_size / 2){
        deflate(v);    
    }

    return 0;
}

/* create a vector
    * @param elem_size: the size of the elements in the vector
    * @param opts: the options for the vector
    * @return a pointer to the vector
*/
vector* create_vector(int elem_size, vector_options* opts){
    vector* vect = malloc(sizeof(vector));

    vector_options* opt_ptr = &vect->opts;
    if (opts == NULL){
        opt_ptr->deflate_enable = DEFAULT_DEFLATE_MODE;
        opt_ptr->inflation = DEFAULT_FLATION;
        opt_ptr->init_arrsize = DEFAULT_INIT_ELEMCOUNT;
        opt_ptr->min_elems = DEFAULT_MIN_ELEMS;
    }
    else memcpy(opt_ptr, opts, sizeof(vector_options));


    vect->elem_count = 0;
    vect->elem_size = elem_size;
    vect->inflations = 0;
    vect->arr_size = opt_ptr->init_arrsize;
    vect->array = malloc(elem_size * vect->arr_size);

    return vect;
}

int traverse_list(vector* v, void* (*cb)(void*, int index)){
    int i = 0;
    int to = v->elem_count;

    while(i < to){
        cb((char*)v->array + (i * v->elem_size), i++);
    }

    return 0;
}

/* destroy a vector
    * @param v: the vector to destroy
    * @return 0 if the vector was destroyed successfully, NULL_VECTOR if the vector is NULL
*/
int destroy_vector(vector* v){
    if (v == NULL) return NULL_VECTOR;
    free(v->array);
    free(v);
    return 0;
}
