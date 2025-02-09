#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#include "Common.h"
#include "Pool.h"

const char* NUMBER_STATUS[2] = {"FREE", "IN USE"};

ClientNode * ClientNode_create(pid_t client_pid, char *status)
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

PoolNode * PoolNode_create(int value, ClientNode *client)
{
    PoolNode *node = (PoolNode *) malloc(sizeof(PoolNode));
    if (node != NULL)
    {
        node->value = value;
        node->status = IN_USE;

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

PoolNode * PoolNode_search(LList *llist, int value)
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

int PoolNode_has_value(LList *llist, int value)
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

void PoolList_print(LList *llist)
{
    if (llist->head != NULL)
    {
        int pool_node_count = 1;
        PoolNode *pool_node = (PoolNode *) llist->head;
        while(pool_node != NULL)
        {

            printf("\nPool Node #%d\n-------------\n", pool_node_count);
            printf("Value: %d\n", pool_node->value);
            printf("Status: %s\n", NUMBER_STATUS[pool_node->status]);
            ClientList_print(pool_node->current_client);
            printf("------------------------------------------\n");
            pool_node = pool_node->next;
            pool_node_count++;
        }
    }
    else 
    {
        printf(" Error: Pool list is NULL\n");
    }
}

void ClientList_print(ClientNode *client_node)
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
