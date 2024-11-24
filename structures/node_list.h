#ifndef NODE_LIST_H
#define NODE_LIST_H

#include "../core/node.h"

typedef struct Node_list{
    int elem_size;
    int elem_count;
    node* root;
}node_list;

node_list* create_nodelist(int elem_size);
int add(node_list* l,void* E, int index);
int push(node_list* l, void* E);
void* get(node_list* l, int index);
int removeIndex(node_list* l, int index, void* retData);
int destoy_nodelist(node_list* l);
int traverse_list(node_list* l, void* (*cb)(void*, int index));

#endif

