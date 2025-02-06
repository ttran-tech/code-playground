#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Response.h"
#include "Common.h"

// Response generate_response(pid_t client_id, int value)
// {
//     Response response;
//     response.client_id = client_id;
//     response.value = value;
//     return response;
// }

void write_response(pid_t client_id, int response_type, int value)
{
    int fd;
    mkfifo(FIFO_PATH, FIFO_PERMISSION);
    printf("Response:\n Process ID: %d\n Value: %d", client_id, value);
    //Handle write end
    Response response;
    response.client_id = client_id;
    response.response_type = response_type;
    response.value = value;

    fd = open(FIFO_PATH, O_WRONLY);
    write(fd, &response, sizeof(response));
    //write(fd, &response, sizeof(response));
    close(fd);
}