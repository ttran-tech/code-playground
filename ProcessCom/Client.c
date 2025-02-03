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
    mkfifo(FIFO_PATH, 0666);

    while (TRUE)
    {
        Data pipe_data;
        pipe_data.process_id = getpid();

        printf("Enter request: ");
        scanf("%d", &pipe_data.request);
        printf("Enter value: ");
        scanf("%d", &pipe_data.value);

        fd = open(FIFO_PATH, O_WRONLY);
        write(fd, &pipe_data, sizeof(pipe_data));
        close(fd);
    }

    return 0;
}