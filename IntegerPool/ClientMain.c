#include "Client.h"

int main()
{
    LList *number_list = llist_init();
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

        process_response(number_list);
    }
}