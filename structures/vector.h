#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define DEFLATE_ENABLE 0
#define DEFLATE_DISABLE 1

typedef enum {
    NULL_VECTOR = 2,
    INDEX_OUT_BOUND
} error_codes;

typedef enum inflation {
    GREEDY,
    CONSERVATIVE
} inflation;

typedef struct {
    size_t elem_size;
    long long arr_size; 
    long long elem_count;
    int deflate_enable;
    long long min_arrsize;
    void *array;
    inflation inflation;
} init_array_options;

typedef struct {
    int deflate_enable;
    long long init_arrsize;
    long long min_arrsize;
    inflation inflation;
} vector_options;

typedef struct {
    size_t elem_size;
    long long elem_count;
    long long arr_size;
    int inflations;
    void* array;
    vector_options opts;
} vector;


int add(vector* v, void* E, long long index);
int push(vector* v, void* E);
void* get(vector* v, long long index);
int removeIndex(vector* v, long long index, void* ret_E);
vector* create_vector(size_t elem_size, vector_options* opts);
int destroy_vector(vector* v);
int traverse_list(vector* v, void* (*cb)(void*, long long index));
long long get_size(vector* v);


vector* create_vector_from_array(init_array_options init);

#endif