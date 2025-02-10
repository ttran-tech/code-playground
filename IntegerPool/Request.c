#include <stdio.h>
#include <stdlib.h>

#include "Common.h"
#include "LList.h"
#include "Request.h"
#include "Pool.h"

void handle_request(Request request, LList *pool_list)
{
    int request_type = request.request_type;
    switch(request_type)
    {
        case REQUEST_NUMBER:
            request_number(request, pool_list); break;
        case RELEASE_NUMBER:
            release_number(request, pool_list); break;
        default:
            printf(" *** Invalid request\n"); break;
    }
}

void request_number(Request request, LList *pool_list)
{
    if (LList_is_empty(pool_list)) // handle the case when the pool_list is empty
    {
        ClientNode *client_node = ClientNode_create(request.process_id, "in use"); // assign the client to the number
        PoolNode *pool_node = PoolNode_create(request.value, client_node);

        // adding requested number to the pool_list
        pool_list->head = (void *) pool_node;
        pool_list->tail = (void *) pool_node;
        pool_list->size++;
        write_response(request.process_id, GRANTED, request.value);
    }
    else
    {
        // when the pool_list is not empty and requested number exist in the list
        if (PoolNode_has_value(pool_list, request.value))
        {
            PoolNode *pool_node = PoolNode_search(pool_list, request.value);

            if (pool_node->status == POOL_NODE_FREE) // assign the client to the number if the number (pool_node) status is FREE
            {
                ClientNode *client_node = ClientNode_create(request.process_id, "in use");
                pool_node->current_client = client_node;
                pool_node->status = POOL_NODE_IN_USE;
                write_response(request.process_id, GRANTED, request.value);
            }
            else if (pool_node->status == POOL_NODE_IN_USE)
            {
                write_response(request.process_id, DENIED, -1);
            }
        }
        else // when the pool_list is not empty but requested number does not exist in the list
        {
            ClientNode *client_node = ClientNode_create(request.process_id, "in use");
            PoolNode *pool_node = PoolNode_create(request.value, client_node);

            // adding the node (requested number) to the pool_list
            ((PoolNode *) pool_list->tail)->next = pool_node; // point the next node of the tail to the new node
            pool_list->tail = (void *) pool_node; // point the tail to the new node; new node is now became the tail
            pool_list->size++;
            write_response(request.process_id, GRANTED, request.value);
        }
    }
}

void release_number(Request request, LList *pool_list)
{
    // check if request value exist in the pool list
    if (PoolNode_has_value(pool_list, request.value))
    {
        PoolNode *pool_node = PoolNode_search(pool_list, request.value);
        if (pool_node != NULL)
        {
            ClientNode *client_node = pool_node->current_client;
            free(client_node);
            pool_node->current_client = NULL;
            pool_node->status = POOL_NODE_FREE;
        }
    }
}

void print_request(Request request)
{
    printf("Process ID: %d\nRequest Type: %d\nValue: %d\n", request.process_id, request.request_type, request.value);
}