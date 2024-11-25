#ifndef NODE_H
#define NODE_H


//dynamic data node
typedef struct Node {
    void* dataPtr;
    struct Node* next;
} node;

node* create_node(int data_size, node* next);
void delete_node(node* n);
void traverse_nodes(node* root, int (*cb)(node*));


#endif