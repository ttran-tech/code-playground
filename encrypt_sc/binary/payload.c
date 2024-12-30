#include <stdio.h>

int payload() {
    char *message = "Payload Executed: Hello there!";
    printf("%s\n", message);
    return 5;
}