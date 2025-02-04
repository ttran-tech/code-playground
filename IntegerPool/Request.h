#ifndef REQUEST_H
#define REQUEST_H

#include <sys/types.h>

typedef struct Request
{
    pid_t process_id;
    int request_type;
    int value;
} Request;

void request_number(Request request);
void release_number(Request request);
void handle_request(Request request);
void print_request(Request request);

#endif