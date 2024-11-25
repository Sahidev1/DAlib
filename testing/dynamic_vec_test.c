
#include <stdio.h>
#include "../structures/vector.h"


typedef struct {
    int x;
    int y;
} point;

int main(int argc, char** argv){
    vector *v = create_vector(sizeof(point), NULL);

    int cmd = 999;

    while(cmd){
        printf("1. Add\n2. Remove\n3. Print\n4. get\n5. Add at\n6. Exit\n");
        scanf("%d", &cmd);

        switch(cmd){
            case 1:
                {
                    point p;
                    printf("Enter x: ");
                    scanf("%d", &p.x);
                    printf("Enter y: ");
                    scanf("%d", &p.y);
                    push(v, &p);
                }
                break;
            case 2:
                {
                    long long index;
                    printf("Enter index: ");
                    scanf("%lld", &index);
                    removeIndex(v, index, NULL);
                }
                break;
            case 3:
                {
                    point* p;
                    for (long long i = 0; i < get_size(v); i++){
                        p = get(v, i);
                        printf("index: %lld, x: %d, y: %d\n", i, p->x, p->y);
                    }
                }
                break;
            case 4:
                {
                    long long index;
                    printf("Enter index: ");
                    scanf("%lld", &index);
                    point* p = get(v, index);
                    if (p != NULL){
                        printf("index: %lld, x: %d, y: %d\n", index, p->x, p->y);
                    } else {
                        printf("index out of bounds\n");
                    }
                }
                break;
            case 5:
                {
                    point p;
                    long long index;
                    printf("Enter x: ");
                    scanf("%d", &p.x);
                    printf("Enter y: ");
                    scanf("%d", &p.y);
                    printf("Enter index: ");
                    scanf("%lld", &index);
                    add(v, &p, index);
                }
                break;
            case 6:
                cmd = 0;
                break;
        }
    }
}