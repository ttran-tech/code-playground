#ifndef COMMON_H
#define COMMON_H

#include <sys/types.h>

#define NUMBER_LIST_SIZE 5
#define TRUE 1
#define FALSE 0

// Pipe
#define FIFO_PATH "/tmp/integerpool_fifo"
#define FIFO_PERMISSION 0666

// Request type
#define REQUEST_NUMBER 1
#define RELEASE_NUMBER 2
#define EXIT 3

typedef struct Request
{
    pid_t process_id;
    int request_type;
    int value;
} Request;

#endif