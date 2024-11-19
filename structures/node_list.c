#include "node_list.h"
#include "node.h"
#include <stdlib.h>
#include <string.h>

node_list* create_nodelist(int elem_size){
    node_list* l = malloc(sizeof(node_list));
    l->elem_size = elem_size;
    l->elem_count = 0;
    l->root = NULL;
}

//O(1)
int add(node_list* l,void* E){
    l->root = create_node(l->elem_size, l->root);
    memcpy(l->root->dataPtr, E, l->elem_size);
    l->elem_count++;
    return 0;
}

//O(index)
void* get(node_list* l, int index){
    if (index >= l->elem_count) return NULL;
    node* curr = l->root;

    int i = 0;
    while(curr != NULL && i++ < index){
        curr = curr->next;
    }

    if (curr == NULL) return NULL;
    return curr->dataPtr;
}

//O(index)
int remove(node_list* l, int index, void* retData){
    if (index >= l->elem_count) return -1;
    node* curr = l->root;

    node* prev = NULL;
    int i = 0;
    while(curr != NULL && i++ < index){
        prev = curr;
        curr = curr->next;
    }

    if(curr == NULL) return -1;

    prev->next = curr->next;
    if(retData != NULL) memcpy(retData, curr->dataPtr, l->elem_size);
    delete_node(curr);
    l->elem_count--;
    return 0;
}

int destoy_nodelist(node_list* l){
    node* root = l->root;

    node* tmp;
    while(root != NULL){
        tmp = root;
        root = root->next;
        delete_node(tmp);
    }

    free(l);

    return 1;
}

