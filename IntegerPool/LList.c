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

// void * LList_search(LList *llist, int value)
// {
//     void *node = llist->head;
//     if (node != NULL)
//     {
//         while (node != NULL)
//         {
//             if (node->value == value)
//             {
//                 return node;
//             }
//             node = node->next;
//         }
//     }
//     return NULL;
// }

// int LList_has(LList *llist, int value)
// {
//     PoolNode *node = llist->head;
//     if (node != NULL)
//     {
//         while (node != NULL)
//         {
//             if (node->value == value)
//             {
//                 return TRUE;
//             }
//             node = node->next;
//         }
//     }
//     return FALSE;
// }