#include "Number.h"

NumberNode * NumberNode_search(LList *llist, int value)
{
    NumberNode *node = llist->head;
    if (node != NULL)
    {
        while (node != NULL)
        {
            if (node->value == value)
            {
                return node;
            }
            node = node->next;
        }
    }
    return NULL;
}

int NumberNode_has_value(LList *llist, int value)
{
    
}