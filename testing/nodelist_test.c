#include "../structures/node_list.h"
#include <stdio.h>
#include <stdlib.h>

void* fun(void * v, int index){
    int* a = v;
    printf("index: %d, value: %d\n", index, *a);
}


int main(int argc, char** argv){

    int ARR_SIZE = 3000;
    int arr[ARR_SIZE];

    srand(3);

    node_list* l = create_nodelist(sizeof(int));

    for (int i = 0; i < ARR_SIZE; i++){
        arr[i] = rand() % 1000;
        add(l, &arr[i]);
    }

    traverse_list(l, fun);




    for (int i = 0; i < 2950; i++){
        removeIndex(l, rand()%30, NULL);
    }

    printf("\n\n\n");
    traverse_list(l, fun);

    destoy_nodelist(l);

    return 0;
} 