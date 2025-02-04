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

}

void release_number(Request request, LList *pool_list)
{

}

void print_request(Request request)
{
    printf("Process ID: %d\nRequest Type: %d\nValue: %d\n", request.process_id, request.request_type, request.value);
}