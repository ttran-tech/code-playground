#ifndef DATA_H
#define DATA_H

#include <sys/types.h>

#define REQUEST 1
#define RELEASE 2
#define TRUE 1
#define FALSE 0

#define BUFFER_SIZE 100

char *FIFO_PATH = "/tmp/myfifo";

typedef struct Data
{
    pid_t process_id;
    int request;
    int value;
} Data;

#endif