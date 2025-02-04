#include <stdio.h>
#include <stdlib.h>
#include "Request.h"
#include "Common.h"
#include "Pool.h"


void request_number(Request request)
{

}

void release_number(Request request)
{

}

void handle_request(Request request)
{
    int request_type = request.request_type;
    switch(request_type)
    {
        case REQUEST_NUMBER:
            request_number(request); break;
        case RELEASE_NUMBER:
            release_number(request); break;
        default:
            printf(" *** Invalid request\n"); break;
    }
}

void print_request(Request request)
{
    printf("Process ID: %d\nRequest Type: %d\nValue: %d\n", request.process_id, request.request_type, request.value);
}