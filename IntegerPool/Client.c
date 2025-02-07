#include <errno.h>
#include <unistd.h>

#include "Client.h"

int print_menu()
{
    int choice;
    printf("---------------------------------\n");
    printf("1. Request a number\n");
    printf("2. Release a number\n");
    printf("3. View number list\n");
    printf("4. Exit\n");
    printf("\nChoice: ");
    scanf("%d", &choice);
    return choice;
}

void client_request_number(LList *number_list)
{
    int number;
    printf("---------------------------------\n");
    printf("Request a number\n");
    printf("Enter a number: ");
    scanf("%d", &number);

    // create a request
    Request request;
    request.process_id = getpid();
    request.request_type = REQUEST_NUMBER;
    request.value = number;

    // send request to the server
    int fd;
    mkfifo(FIFO_PATH, FIFO_PERMISSION);
    printf("---------------------------------\n");
    printf("Sending request...");

    fd = open(FIFO_PATH, O_WRONLY);
    if (write(fd, &request, sizeof(request)) != -1)
    {
        printf("Done\n");
    }
    close(fd);

    printf("---------------------------------\n");
    process_response(number_list);
}

void client_release_number(LList *number_list)
{
    int number_index;
    printf("---------------------------------\n");
    printf("Release a number\n");
    for (int i = 0; i < NUMBER_LIST_SIZE; i++)
    {
        //printf("%d - %d\n", i, number_list[i]);
    }
    printf("\nEnter number index: ");
    scanf("%d", &number_index);

    // create a request
    // Request request;
    // request.process_id = getpid();
    // request.request_type = RELEASE_NUMBER;
    // request.value = number_list[number_index];

    // send request to the server

    // remove number from the number list
}

void process_response(LList *number_list)
{
    Response response;
    int fd;

    printf(" *** Obtaining mkfifo...");
    if (mkfifo(FIFO_PATH, FIFO_PERMISSION) == -1 && errno != EEXIST)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    printf("Done\n");

    printf(" *** Opening FIFO...");
    while((fd = open(FIFO_PATH, O_RDONLY)) == -1)
    {
        perror("open");
        printf("Retry opening FIFO...\n");
        usleep(1000000); // Sleep for 100ms before retrying
    }
    printf("Done\n");

    printf(" *** Reading response...");
    while (read(fd, &response, sizeof(response)) == -1)
    {
        perror("read");
        printf("Retry reading response...\n");
        usleep(1000000); // Sleep for 100ms before retrying
    }
    close(fd);
    printf("Done\n");
    
    printf(" *** Response received...\n");
    printf("---------------------------------\n");
    printf(" >> Response Type: %d (1 = GRANTED, 2 = WAITING)\n", response.response_type);
    
    if (response.response_type == GRANTED)
    {
        printf(" >> Process ID: %d | Value: %d\n", response.client_id, response.value);
    }
    else if (response.response_type == WAITING)
    {
        printf(" >> Number is in-used\n");
    }

    // if (response.client_id == getpid())
    // {
    //     NumberNode *number_node = (NumberNode *) malloc(sizeof(NumberNode));
    //     if (number_node != NULL)
    //     {
    //         number_node->value = response.value;
    //         number_node->next = NULL;
    //     }

    //     if (number_list->size != 0)
    //     {
    //         number_list->head = (void *) number_node;
    //         number_list->tail = number_list->head;
    //         number_list->size++;
    //     }
    //     else
    //     {
    //         ((NumberNode *) number_list->tail)->next = number_node;
    //         number_list->tail = (void *) number_node;
    //         number_list->size++;
    //     }
    // }
}

void print_number_list(LList *number_list)
{
    NumberNode *number_node = (NumberNode *) number_list->head;
    
    printf("Number List:\n [ ");
    while (number_node != NULL)
    {
        int value = number_node->value;
        printf("%d ", value);
        number_node = number_node->next;
    }
    printf("]\n");
}