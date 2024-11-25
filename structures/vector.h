#ifndef VECTOR_H
#define VECTOR_H

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

typedef enum inflation deflation;

typedef struct {
    int deflate_enable;
    int init_arrsize;
    int min_elems;
    inflation inflation;
} vector_options;

typedef struct {
    int elem_size;
    int elem_count;
    int arr_size;
    int inflations;
    void* array;
    vector_options opts;
} vector;

int add(vector* v, void* E, int index);
int push(vector* v, void* E);
int removeIndex(vector* v, int index, void* ret_E);
vector* create_vector(int elem_size, vector_options* opts);
int destroy_vector(vector* v);
int traverse_list(vector* v, void* (*cb)(void*, int index));

#endif