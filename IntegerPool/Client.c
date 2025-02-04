#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Common.h"
#include "Request.h"

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

void client_request_number(int *number_list)
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

void client_release_number(int *number_list)
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
    Request request;
    request.process_id = getpid();
    request.request_type = RELEASE_NUMBER;
    request.value = number_list[number_index];

    // send request to the server

    // remove number from the number list
}

int main()
{
    int number_list[NUMBER_LIST_SIZE];
    int menu_choice = 0;

    while (TRUE)
    {
        menu_choice = print_menu();

        if (menu_choice == REQUEST_NUMBER)
        {
            client_request_number(number_list);
        }
        else if (menu_choice == RELEASE_NUMBER)
        {
            client_release_number(number_list);
        }
        else if (menu_choice == EXIT)
        {
            break;
        }
        else
        {
            printf(" *** Invalid choice\n");
        }
    }
}