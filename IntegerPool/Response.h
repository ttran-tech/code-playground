#ifndef RESPONSE_H
#define RESPONSE_H

#include <sys/types.h>
#include "Pool.h"

typedef struct Response
{
    pid_t client_id;
    int value;
} Response;

Response generate_response(pid_t client_id, int value);

#endif