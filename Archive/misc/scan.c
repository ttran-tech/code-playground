#include <stdio.h>
#include <stdlib.h>

#define TRUE 1

int printMenu()
{
	int choice = -1;

	printf("1. Addition\n");
	printf("2. Subtraction\n");
	printf("3. Exit\n");
	printf("\nChoice: ");
	scanf("%d", &choice);
	printf("your choice: %d\n", choice);
	return choice;
}

void add()
{
	int x, y;
	printf("Enter integer 1: ");
	scanf("%d", &x);
	printf("Enter integer 2: ");
	scanf("%d", &y);
	printf("%d + %d = %d\n", x, y, x+y);
}

void subtract()
{
	int x, y;
	printf("Enter integer 1: ");
	scanf("%d", &x);
	printf("Enter integer 2: ");
	scanf("%d", &y);
	printf("%d - %d = %d\n", x, y, x-y);
}

int main()
{
	int choice;
	
	while(TRUE)
	{
		choice = printMenu();
		
		if (choice == 1)
		{
			add();
		}
		else if (choice == 2)
		{
			subtract();
		}
		else if (choice == 3)
		{
			break;
		}
		else
		{
			printf("Invalid choice\n");
		}
	}
	
	return 0;
}