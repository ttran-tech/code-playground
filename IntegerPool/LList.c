#include "Common.h"
#include "LList.h"

LList * LList_init()
{
    LList *llist = (LList *) malloc(sizeof(LList));
    llist->head = NULL;
    llist->tail = NULL;
    llist->size = 0;
    return llist;
}

int LList_is_empty(LList *llist)
{
    return (llist->size == 0);
}