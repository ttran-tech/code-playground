#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Common.h"
#include "Request.h"
#include "Pool.h"

LList *pool_list;

int main()
{
    int fd;
    mkfifo(FIFO_PATH, FIFO_PERMISSION);

    Request request;
    pool_list = llist_init();

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