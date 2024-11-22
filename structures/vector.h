#ifndef VECTOR_H
#define VECTOR_H

#define DEFLATE_ENABLE 0
#define DEFLATE_DISABLE 1

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
    deflation deflation;
} vector_options;

typedef struct {
    int elem_size;
    int elem_count;
    int inflations;
    void* array;
    vector_options opts;
} vector;

#endif