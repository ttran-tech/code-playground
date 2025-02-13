#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Data.h"

int main()
{
    int fd;
    mkfifo(FIFO_PATH, 0666); // Make FIFO with a pathname /tmp/myfifo
    
    //char pipe_data[BUFFER_SIZE] = {0}; // Format as: <Process ID>:<Request>:<Value>
    Data pipe_data;

    while (TRUE)
    {
        printf("Waiting for request...\n");
        fd = open(FIFO_PATH, O_RDONLY); // O_RDONLY defined in fcntl.h
        read(fd, &pipe_data, sizeof(pipe_data));
        printf("\nReceive data from Process ID:%d\n Request: %s\n Value: %d\n\n", pipe_data.process_id, (pipe_data.request == 1) ? "REQUEST":"RELEASE", pipe_data.value);
        close(fd);
    }

    return 0;
}