#include "Client.h"

int print_menu()
{
    int choice;
    printf("\n---------------------------------\n");
    printf("1. Request a number\n");
    printf("2. Release a number\n");
    printf("3. Exit\n");
    printf("\nChoice: ");
    scanf("%d", &choice);
    return choice;
}

void client_request_number(LList *number_list)
{
    int number;
    printf("\n---------------------------------\n");
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
    printf("Sending request...");
    fd = open(FIFO_PATH, O_WRONLY);
    if (write(fd, &request, sizeof(request)) != -1)
    {
        printf("Done\n");
    }
    close(fd);

    // add the number into the number list
}

void client_release_number(LList *number_list)
{
    int number_index;
    printf("\n---------------------------------\n");
    printf("Release a number\n");
    for (int i = 0; i < NUMBER_LIST_SIZE; i++)
    {
        printf("%d - %d\n", i, number_list[i]);
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
    mkfifo(FIFO_PATH, FIFO_PERMISSION);
    fd = open(FIFO_PATH, FIFO_PERMISSION);
    read(fd, &response, sizeof(Response));
    if (response.client_id == getpid())
    {
        NumberNode *number_node = (NumberNode *) malloc(sizeof(NumberNode));
        if (number_node != NULL)
        {
            number_node->value = response.value;
            number_node->next = NULL;
        }

        if (number_list->size != 0)
        {
            number_list->head = (void *) number_node;
            number_list->tail = number_list->head;
            number_list->size++;
        }
        else
        {
            ((NumberNode *) number_list->tail)->next = number_node;
            number_list->tail = (void *) number_node;
            number_list->size++;
        }
    }
}

