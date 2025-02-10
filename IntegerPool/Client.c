#include <errno.h>
#include <unistd.h>

#include "Client.h"
#include "Number.h"

const char* RESPONSE_TYPE[2] = {"DENIED", "GRANTED"};

int print_menu()
{
    int choice;
    printf("1. Request Number\n");
    printf("2. Release Number\n");
    printf("3. View No.List\n");
    printf("4. Exit\n");
    printf("\nChoice: ");
    scanf("%d", &choice);

    printf("-----------------------------------------------\n");
    return choice;
}

void client_request_number(LList *number_list)
{
    int number;
    printf("[ REQUEST NUMBER ]\n");
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
    printf("-----------------------------------------------\n");
    printf("Sending request...");

    fd = open(FIFO_PATH, O_WRONLY);
    if (write(fd, &request, sizeof(request)) != -1)
    {
        printf("Done\n");
    }
    close(fd);

    printf("-----------------------------------------------\n");
    process_response(number_list);
}

void client_release_number(LList *number_list)
{
    int value;
    printf("Release a number\n");
    print_number_list(number_list);

    printf("Enter number: ");
    scanf("%d", &value);

    if (NumberNode_has_value(number_list, value))
    {
        Request request;
        request.process_id = getpid();
        request.request_type = RELEASE_NUMBER;
        request.value = value;

        // send request to the server
        int fd;
        mkfifo(FIFO_PATH, FIFO_PERMISSION);
        printf("-----------------------------------------------\n");
        printf("Sending request...");

        fd = open(FIFO_PATH, O_WRONLY);
        if (write(fd, &request, sizeof(request)) != -1)
        {
            printf("Done\n");
        }
        close(fd);
    }
    else
    {
        printf(" *** Number not found.\n");
    }

    // Release number from the number list
    NumberNode *number_node = NumberNode_search(number_list, value);
    if (number_list->size > 1)
    {
        if (number_node->value == ((NumberNode *) number_list->head)->value) // case number_node is the head
        {
            number_list->head = (void *) number_node->next;
            ((NumberNode *) number_list->head)->prev = NULL;
        }
        else if (number_node->value == ((NumberNode *) number_list->tail)->value) // case number_node is the tail
        {
            number_list->tail = (void *) number_node->prev;
            ((NumberNode *) number_list->tail)->next = NULL;
        }
        else // case number_node is in the middle
        {
            number_node->prev->next = number_node->next;
            number_node->next->prev = number_node->prev;
        }
        free(number_node);
        number_list->size--;
    }
    else if (number_list->size == 1)
    {
        free(number_node);  // Do not free number_list because you may request another number.
        number_list->size--;
    }
    print_number_list(number_list);
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
    printf("-----------------------------------------------\n");
    printf(" >> Response Type: %s\n", RESPONSE_TYPE[response.response_type]);
    
    if (response.response_type == GRANTED)
    {
        printf(" >> Process ID: %d | Value: %d\n", response.client_id, response.value);
    }
    else if (response.response_type == DENIED)
    {
        printf(" >> Your request has been denied. The number is in used.\n");
    }
    printf("-----------------------------------------------\n");

    if (response.client_id == getpid())
    {
        if (response.response_type == GRANTED)
        {
            NumberNode *new_number_node = (NumberNode *) malloc(sizeof(NumberNode));
            new_number_node->value = response.value;
            new_number_node->prev = NULL;
            new_number_node->next = NULL;
            if (LList_is_empty(number_list))
            {
                number_list->head = (void *) new_number_node;
                number_list->tail = (void *) new_number_node;
                number_list->size++;
            }
            else
            {
                new_number_node->prev = (NumberNode *) number_list->tail;
                ((NumberNode *)(number_list->tail))->next = new_number_node;
                number_list->tail = (void *) new_number_node;
                number_list->size++;
            }
        }
        print_number_list(number_list);
    }
}

void print_number_list(LList *number_list)
{
    NumberNode *number_node = (NumberNode *) number_list->head;
    
    printf("Number List:\n [");
    while (number_node != NULL)
    {
        int value = number_node->value;
        printf("%d", value);
        (number_node->next != NULL) ? printf(" | "): (void)0;
        number_node = number_node->next;
    }
    printf("]\n");
    printf("-----------------------------------------------\n");
}