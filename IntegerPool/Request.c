#include <stdio.h>
#include <stdlib.h>
#include "Request.h"
#include "Common.h"

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
    if (llist_is_empty(pool_list))
    {
        ClientNode *client_node = create_client_node(request.process_id, "in use");
        PoolNode *pool_node = create_pool_node(request.value, client_node);
        pool_list->head = (void *) pool_node;
        pool_list->tail = (void *) pool_node;
        pool_list->size++;
        write_response(request.process_id, GRANTED ,request.value);
    }
    else
    {
        // value exist in pool_list
        if (llist_is_in_list(pool_list, request.value))
        {
            PoolNode *pool_node = llist_search_by_value(pool_list, request.value);
            ClientNode *client_node = create_client_node(request.process_id, "waiting");

            // add new client to the client list
            ((ClientNode *) pool_node->client_list->tail)->next = client_node;
            pool_node->client_list->tail = (void *) client_node;
            pool_node->client_list->size++;
            write_response(-1, WAITING, -1);
        }
        else 
        {
            ClientNode *client_node = create_client_node(request.process_id, "in use");
            PoolNode *pool_node = create_pool_node(request.value, client_node);
            ((PoolNode *) pool_list->tail)->next = pool_node; // point the next node of the tail to the new node
            pool_list->tail = (void *) pool_node; // point the tail to the new node; new node is now became the tail
            pool_list->size++;
            write_response(request.process_id, GRANTED, request.value);
        }
    }
}

void release_number(Request request, LList *pool_list)
{

}

void print_request(Request request)
{
    printf("Process ID: %d\nRequest Type: %d\nValue: %d\n", request.process_id, request.request_type, request.value);
}