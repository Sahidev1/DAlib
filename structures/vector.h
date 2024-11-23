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

#endif