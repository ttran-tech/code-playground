#include <stdio.h>
#include <assert.h>

int main() {
    int i = 5;
    int j = 10;
    assert(i == j);
    printf("assert passed\n");

    return 0;
}