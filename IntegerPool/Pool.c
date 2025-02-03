#include <stdlib.h>
#include <stdio.h>
#include "Pool.h"

LList * llist_init()
{
    LList *llist = (LList *) malloc(sizeof(LList));
    llist->head = NULL;
    llist->tail = NULL;
    llist->list_size = 0;
    return llist;
}

PoolNode * create_new_node(int value, ClientNode *client)
{
    PoolNode *node = (PoolNode *) malloc(sizeof(PoolNode));
    if (node != NULL)
    {
        node->value = value;
        node->is_in_use = 1;
        node->client = client;
        node->next = NULL;
    }
    return node;
}