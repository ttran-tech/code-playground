#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Pool.h"
#include "Request.h"
#include "Common.h"

extern LList *pool_list;

int main()
{
    int value;

    Request request;
    request.process_id = getpid();
    request.request_type = REQUEST_NUMBER;
    request.value = 5;

    pool_list = llist_init();
    value = handle_request(request, pool_list);

    print_pool_list(pool_list);

    printf(" >>> Returned value = %d\n", value);

    return 0;
}
