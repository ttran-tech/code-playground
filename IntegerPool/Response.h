#ifndef RESPONSE_H
#define RESPONSE_H

#include <sys/types.h>
#include "Pool.h"

typedef struct Response
{
    pid_t client_id;
    int value;
} Response;

void response_init(Response *response);
Response generate_response(pid_t client_id, int value);
void write_response(Response *response);

#endif