
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../structures/vector.h"

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

    // create vector test
    vector* v = create_vector(sizeof(test_elem), NULL);
    assert(v != NULL);
    assert(v->elem_count == 0);
    assert(v->elem_size == sizeof(test_elem));

    // add element test
    test_elem e;
    init_test_elem(&e, 32,45, "test");
    assert(add(v, &e, 4) != 0);
    assert(add(v, &e, 0) == 0);
    assert (v->elem_count == 1);
    assert(get_size(v) == 1);

    // get element test
    test_elem* saved_elem = get(v, 2);
    assert(saved_elem == NULL);
    saved_elem = get(v,0);
    assert(saved_elem != NULL);
    assert(strcmp(saved_elem->msg, e.msg)== 0);
    assert(saved_elem->x == e.x);
    assert(saved_elem->y == e.y);

    //push test
    init_test_elem(&e, 11, 25, "cool");
    assert(push(v, &e) == 0);
    assert(v->elem_count == 2);
    assert(get_size(v) == 2);
    

    //remove test

    assert(removeIndex(v, 0, &e) == 0);    
    assert(get_size(v) == 1);
    assert(e.x == 32);
    assert(removeIndex(v,0,&e) == 0);
    assert(get_size(v) == 0);
    assert(e.x == 11);

    printf("unit test successfull\n");
    return 0;
}