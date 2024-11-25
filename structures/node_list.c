#include "node_list.h"
#include "../core/node.h"
#include <stdlib.h>
#include <string.h>

node_list* create_nodelist(size_t elem_size){
    node_list* l = malloc(sizeof(node_list));
    l->elem_size = elem_size;
    l->elem_count = 0;
    l->root = NULL;
}

long long get_size(node_list* l){
    return l->elem_count;
}

//O(n)
int push(node_list* l,void* E){
    return add(l, E, l->elem_count);
}

int add(node_list* l, void* E, long long index){
    if(index > l->elem_count || index < 0) return 1;
    node* curr = l->root;
    if(curr == NULL){
        l->root = create_node(l->elem_size, NULL);
        memcpy(l->root->dataPtr, E, l->elem_size);
        l->elem_count++;
        return 0;
    }
    node* prev = NULL;
    long long i = 0;
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
void* get(node_list* l, long long index){
    if (index >= l->elem_count) return NULL;
    node* curr = l->root;

    long long i = 0;
    while(curr != NULL && i++ < index){
        curr = curr->next;
    }

    if (curr == NULL) return NULL;
    return curr->dataPtr;
}

//O(index)
int removeIndex(node_list* l, long long index, void* retData){
    if (index >= l->elem_count) return -1;
    node* curr = l->root;

    node* prev = NULL;
    long long i = 0;
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

int iterate_callback(node_list* l, long long from, long long to_excl, void* (*cb)(void*, long long index)){
    if(l == NULL) return 1;
    if(from < 0 || from >= l->elem_count) return 1;
    if(to_excl < 0 || to_excl >= l->elem_count || to_excl < from) return 1;

    node* curr = l->root;
    long long i = 0;
    while(i < from){
        if(curr == NULL) return 1;
        curr = curr->next;
        i++;
    }

    while(i < to_excl){
        if(curr == NULL) return 1;
        cb(curr->dataPtr, i++);
        curr = curr->next;
    }

    return 0;
}

int traverse_list(node_list* l, void* (*cb)(void*, long long index)){
    node* curr = l->root;
    long long i = 0;
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

