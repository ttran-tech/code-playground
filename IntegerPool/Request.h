#ifndef REQUEST_H
#define REQUEST_H

#include <sys/types.h>
#include "Pool.h"

typedef struct Request
{
    pid_t process_id;
    int request_type;
    int value;
} Request;

void handle_request(Request request, LList *pool_list);
void request_number(Request request, LList *pool_list);
void release_number(Request request, LList *pool_list);
void print_request(Request request);

#endif