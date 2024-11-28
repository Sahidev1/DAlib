
#include "vector.h"

typedef enum {
    MIN,
    MAX
} prio_type;

typedef struct {
    prio_type prio_type;
    int (*comparator) (void* e1, void* e2);
    vector* tree;
} prioQ;