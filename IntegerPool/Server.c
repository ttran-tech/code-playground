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

void print_request(Request request)
{
    printf("Process ID: %d\nRequest Type: %d\nValue: %d\n", request.process_id, request.request_type, request.value);
}


int main()
{
    int fd;
    mkfifo(FIFO_PATH, FIFO_PERMISSION);

    Request request;
    LList *pool_list = llist_init();

    printf("Server started.\n");
    while (TRUE)
    {
        printf("Waiting for request...\n");
        
        // Handle read end
        fd = open(FIFO_PATH, O_RDONLY);
        read(fd, &request, sizeof(request));
        print_request(request);
        handle_request(request);
        close(fd);

        // Handle write end


    }
    return 0;
}