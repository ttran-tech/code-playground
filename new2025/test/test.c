#include <stdio.h>
#include <unistd.h>

int main()
{
    char post_data[256];
    sprintf(post_data, "{\"pid\": \"%d\"}", getpid());

    printf("%s\n", post_data);

    return 0;
}