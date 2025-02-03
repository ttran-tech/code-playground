#include <stdio.h>
#include <unistd.h>

#define SIZE 5

struct Routine {
    void *r[SIZE];
};

void foo()
{
    printf("foo(): Hello world!\n");
}

int main()
{
    struct Routine routine;

    routine.r[0] = (void *) foo;

    ((void (*)()) ((void *) routine.r[0]))();

    return 0;
}