#include "../structures/node_list.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int x, y;
    char msg[4];
} test_elem;

int init_test_elem (test_elem* e, int x, int y, char msg[4]){
    e->x = x;
    e->y = y;
    for (int i = 0; i < 4; i++){
        e->msg[i] = msg[i];
    }
}

void* printer(void* E, long long index){
    test_elem* e = (test_elem*) E;
    printf("index: %lld, x: %d, y: %d, msg: %s\n", index, e->x, e->y, e->msg);
}
 
int main(int argc, char** argv){
    
    // create node test
    node_list* list = create_nodelist(sizeof(test_elem));
    assert(list != NULL);
    assert(list->elem_count == 0);
    assert(list->elem_size == sizeof(test_elem));
    assert(list->root == NULL);

    // add element test
    test_elem e;
    init_test_elem(&e, 32,45, "test");
    assert(add(list, &e, 4) != 0);
    assert(add(list, &e, 0) == 0);
    assert(list->root != NULL);
    assert(list->elem_count == 1);
    assert(get_size(list) == 1);

//    traverse_list(list, printer);


    // get element test
    test_elem* saved_elem = get(list, 2);
    assert(saved_elem == NULL);
    saved_elem = get(list, 0);
    assert(saved_elem != NULL);
    assert(strcmp(saved_elem->msg, e.msg) == 0);
    assert(saved_elem->x == e.x);
    assert(saved_elem->y == e.y);

   // traverse_list(list, printer);


    // push test
    init_test_elem(&e, 11, 25, "cool");
    assert(push(list, &e) == 0);
    assert(list->root != NULL);
    assert(list->elem_count == 2);
    assert(get_size(list) == 2);

 //   traverse_list(list, printer);

    // remove test
    assert(removeIndex(list, 0, &e) == 0);    
    assert(get_size(list) == 1);
    assert(e.x == 32);
    assert(removeIndex(list,0,&e) == 0);
    assert(get_size(list) == 0);
    assert(e.x == 11);


    printf("unit test success\n");
    return 0;
}
