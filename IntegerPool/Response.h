#ifndef RESPONSE_H
#define RESPONSE_H

#include <sys/types.h>
#include "Pool.h"

#define GRANTED 1
#define WAITING 2
#define RELEASE 3

typedef struct Response
{
    pid_t client_id;
    int response_type; // 1 = granted, 2 = waiting
    int value;
} Response;

// void response_init(Response *response);
// Response generate_response(pid_t client_id, int value);
void write_response(pid_t client_id, int response_type, int value);

#endif