#ifndef client_h
#define client_h

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Request.h"
#include "Pool.h"
#include "Common.h"

typedef struct NumberNode {
    int value;
    struct NumberNode *next;
} NumberNode;

int print_menu();
void client_request_number(LList *number_list);
void client_release_number(LList *number_list);
void process_response(LList *number_list);

#endif