#include "node_list.h"
#include "../core/node.h"
#include <stdlib.h>
#include <string.h>

node_list* create_nodelist(int elem_size){
    node_list* l = malloc(sizeof(node_list));
    l->elem_size = elem_size;
    l->elem_count = 0;
    l->root = NULL;
}

//O(n)
int push(node_list* l,void* E){
    return add(l, E, l->elem_count);
}

int add(node_list* l, void* E, int index){
    if(index > l->elem_count || index < 0) return 1;
    node* curr = l->root;
    if(curr == NULL){
        l->root = create_node(l->elem_size, NULL);
        memcpy(l->root->dataPtr, E, l->elem_size);
        l->elem_count++;
        return 0;
    }
    node* prev = NULL;
    int i = 0;
    while(curr != NULL && i < index){
        prev = curr;
        curr = curr->next;
        i++;
    };

    if(prev == NULL){
        l->root = create_node(l->elem_size, NULL);
        memcpy(l->root->dataPtr, E, l->elem_size);
    } 
    else {
        node* n = create_node(l->elem_size, NULL);
        n->next = curr;
        prev->next = n;
        memcpy(prev->dataPtr, E, l->elem_size);
    }
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
int removeIndex(node_list* l, int index, void* retData){
    if (index >= l->elem_count) return -1;
    node* curr = l->root;

    node* prev = NULL;
    int i = 0;
    while(curr != NULL && i++ < index){
        prev = curr;
        curr = curr->next;
    }

    if(curr == NULL) return -1;

    if(prev == NULL) l->root = curr->next;
    else prev->next = curr->next;
    

    if(retData != NULL) memcpy(retData, curr->dataPtr, l->elem_size);
    delete_node(curr);
    l->elem_count--;
    return 0;
}

int traverse_list(node_list* l, void* (*cb)(void*, int index)){
    node* curr = l->root;
    int i = 0;
    while(curr != NULL){
        cb(curr->dataPtr, i++);
        curr = curr->next;
    }
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

