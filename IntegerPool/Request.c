#include <stdio.h>
#include <stdlib.h>
#include "Request.h"
#include "Common.h"

int handle_request(Request request, LList *pool_list)
{
    int request_type, value;
    request_type = request.request_type;
    switch(request_type)
    {
        case REQUEST_NUMBER:
            value = request_number(request, pool_list); break;
        case RELEASE_NUMBER:
            release_number(request, pool_list); break;
        default:
            printf(" *** Invalid request\n"); break;
    }
    return value;
}

int request_number(Request request, LList *pool_list)
{
    if (llist_is_empty(pool_list))
    {
        ClientNode *client_node = create_client_node(request.process_id);
        PoolNode *pool_node = create_pool_node(request.value, client_node);
        pool_list->head = (void *) pool_node;
        pool_list->tail = (void *) pool_node;
        pool_list->size++;
        return request.value;
    }
    else
    {

    }
}

void release_number(Request request, LList *pool_list)
{

}

void print_request(Request request)
{
    printf("Process ID: %d\nRequest Type: %d\nValue: %d\n", request.process_id, request.request_type, request.value);
}