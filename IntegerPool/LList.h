#ifndef llist_h
#define llist_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct LList
{
    void *head;
    void *tail;
    size_t size;
} LList;

// LList operators
LList * LList_init();
int LList_is_empty(LList *llist);
// void * LList_search(LList *llist, int value);
// int LList_has(LList *llist, int value);

#endif