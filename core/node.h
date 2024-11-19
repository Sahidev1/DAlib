#ifndef NODE_H
#define NODE_H


//dynamic data node
typedef struct Node {
    void* dataPtr;
    int size;
    struct Node* next;
} node;

node* create_node(int size, node* next);
void delete_node(node* n);
void traverse_nodes(node* root, int (*cb)(node*));


#endif