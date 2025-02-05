#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "Pool.h"
#include "Common.h"

ClientNode * create_client_node(pid_t client_pid, const char *status)
{
    ClientNode *client_node = (ClientNode *) malloc(sizeof(ClientNode));
    if (client_node != NULL)
    {
        client_node->client_pid = client_pid;
        client_node->status = status;
        client_node->next = NULL;
    }
    return client_node;
}

PoolNode * create_pool_node(int value, ClientNode *client)
{
    PoolNode *node = (PoolNode *) malloc(sizeof(PoolNode));
    if (node != NULL)
    {
        node->value = value;
        node->is_in_use = IN_USE;

        // create client list
        LList *client_list = (LList *) malloc(sizeof(LList));
        if (client_list != NULL)
        {
            client_list->head = (void *) client;
            client_list->tail = (void *) client;
            client_list->size++;

            node->current_client = (ClientNode *) client_list->head;
            node->client_list = client_list;
        }

        node->next = NULL;
    }
    return node;
}

LList * llist_init()
{
    LList *llist = (LList *) malloc(sizeof(LList));
    llist->head = NULL;
    llist->tail = NULL;
    llist->size = 0;
    return llist;
}

int llist_is_empty(LList *llist)
{
    return (llist->size == 0);
}

PoolNode * llist_search_by_value(LList *llist, int value)
{
    PoolNode *node = llist->head;
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

int llist_is_in_list(LList *llist, int value)
{
    PoolNode *node = llist->head;
    if (node != NULL)
    {
        while (node != NULL)
        {
            if (node->value == value)
            {
                return TRUE;
            }
            node = node->next;
        }
    }
    return FALSE;
}

void print_pool_list(LList *llist)
{
    if (llist->head != NULL)
    {
        int pool_node_count = 1;
        PoolNode *pool_node = (PoolNode *) llist->head;
        while(pool_node != NULL)
        {
            printf("Pool Node #%d\n-------------\n", pool_node_count);
            printf("Value: %d\n", pool_node->value);
            printf("In use: %d (1 = in use, 0 = free)\n", pool_node->is_in_use);
            print_client_list(pool_node->current_client);
            printf("\n------------------------------------------\n\n");
            pool_node = pool_node->next;
            pool_node_count++;
        }
    }
    else 
    {
        printf(" Error: Pool list is NULL\n");
    }
}

void print_client_list(ClientNode *client_node)
{
    if (client_node != NULL)
    {
        int client_count = 1;
        printf("[ Client List ]\n");
        while (client_node != NULL)
        {
            printf("Client #%d | PID: %d | Status: %s\n", client_count, client_node->client_pid, client_node->status);
            client_node = client_node->next;
            client_count++;
        }
    }
}