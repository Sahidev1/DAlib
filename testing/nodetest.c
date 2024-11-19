#include "../core/node.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int X;
    int Y;
} Point;

int pointCB(node* n){
    if (n == NULL) return 1;
    Point p = *((Point*)n->dataPtr);
    printf("point x:%d, y:%d\n", p.X, p.Y);
    return 0;
}

int main(int argc, char** argv){

    node* root = create_node(sizeof(Point), NULL);

    Point* p = root->dataPtr;
    p->X = 256;
    p->Y = 128;

    root = create_node(sizeof(Point), root);
    ((Point*) root->dataPtr )->X = 111;
    ((Point*) root->dataPtr )->Y = 233;

    traverse_nodes(root, pointCB);

    return 0;
}