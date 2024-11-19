
#include "node.h"
#include <stdlib.h>

node* create_node(int size, node* next){
    void* mem_chunk = malloc(sizeof(node) + size);
    ((node*) mem_chunk)->dataPtr = mem_chunk + sizeof(node);
    ((node*) mem_chunk)->size = size;
    ((node*) mem_chunk)->next = next;
    return (node*) mem_chunk;
}

void delete_node(node* n){
    free((void *)n);
}


void traverse_nodes(node* root, int (*cb)(node*)){
    node* current = root;
    while(current != NULL){
        cb(current);
        current = current->next;
    }
}