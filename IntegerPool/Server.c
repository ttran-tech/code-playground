#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

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

}

int main()
{
    int fd;
    mkfifo(FIFO_PATH, FIFO_PERMISSION);

    Request request;
    LList *pool_list = llist_init();

    while (TRUE)
    {
        printf("Waiting for request...");
        
        // Handle read end
        fd = open(FIFO_PATH, O_RDONLY);
        read(fd, &request, sizeof(request));
        handle_request(request);
        close(fd);

        // Handle write end


    }
    return 0;
}