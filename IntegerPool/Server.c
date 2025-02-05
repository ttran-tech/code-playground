#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Common.h"
#include "Request.h"
#include "Response.h"
#include "Pool.h"

extern LList *pool_list;

int main()
{
    int fd;
    mkfifo(FIFO_PATH, FIFO_PERMISSION);

    Request request;
    Response response;
    pool_list = llist_init();

    printf("Server started.\n");
    while (TRUE)
    {
        printf("Waiting for request...\n");
        
        // Handle read end
        fd = open(FIFO_PATH, O_RDONLY);
        read(fd, &request, sizeof(request));
        // print_request(request);

        response = handle_request(request, pool_list);
        print_pool_list(pool_list);
        
        close(fd);

        // Handle write end
        fd = open(FIFO_PATH, O_WRONLY);
        write(fd, &response, sizeof(response));
        close(fd);
    }
    return 0;
}