#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Response.h"
#include "Common.h"

void response_init(Response *response)
{
    response->client_id = -1;
    response->value = -99;
}

Response generate_response(pid_t client_id, int value)
{
    Response response;
    response.client_id = client_id;
    response.value = value;
    return response;
}

void write_response(Response *response)
{
    int fd;
    mkfifo(FIFO_PATH, FIFO_PERMISSION);
    printf("Response:\n Process ID: %d\n Value: %d", response->client_id, response->value);
    //Handle write end
    Response res = generate_response(response->client_id, response->value);
    fd = open(FIFO_PATH, O_WRONLY);
    write(fd, &res, sizeof(res));
    //write(fd, &response, sizeof(response));
    close(fd);
}