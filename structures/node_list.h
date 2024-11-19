#ifndef NODE_LIST_H
#define NODE_LIST_H

#include "../core/node.h"

typedef struct Node_list{
    int elem_size;
    int elem_count;
    node* root;
}node_list;

#endif

