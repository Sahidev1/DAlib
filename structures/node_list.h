#ifndef NODE_LIST_H
#define NODE_LIST_H

#include <stddef.h>
#include "../core/node.h"

typedef struct Node_list{
    size_t elem_size;
    long long elem_count;
    node* root;
}node_list;

node_list* create_nodelist(size_t elem_size);
int add(node_list* l,void* E, long long index);
int push(node_list* l, void* E);
void* get(node_list* l, long long index);
int removeIndex(node_list* l, long long index, void* retData);
int destoy_nodelist(node_list* l);
int traverse_list(node_list* l, void* (*cb)(void*, long long index));
int iterate_callback(node_list* l, long long from, long long to_excl, void* (*cb)(void*, long long index));
long long get_size(node_list* l);

#endif

