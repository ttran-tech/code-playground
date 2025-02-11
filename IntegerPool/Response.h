#ifndef RESPONSE_H
#define RESPONSE_H

#include <sys/types.h>
#include "Pool.h"

#define GRANTED 1
#define DENIED 0
#define RELEASE 3

typedef struct Response
{
    pid_t client_id;
    int response_type; // 1 = granted, 0 = denied
    int value;
} Response;

void write_response(pid_t client_id, int response_type, int value);

#endif