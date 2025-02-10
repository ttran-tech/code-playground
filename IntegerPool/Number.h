#ifndef number_h
#define number_h

#include "LList.h"

typedef struct NumberNode {
    int value;
    struct NumberNode *prev;
    struct NumberNode *next;
} NumberNode;

// NumberNode operations
NumberNode * NumberNode_search(LList *llist, int value);
int NumberNode_has_value(LList *llist, int value);

#endif