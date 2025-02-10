#ifndef POOL_H
#define POOL_H

#include "LList.h"

#define POOL_NODE_IN_USE 1
#define POOL_NODE_FREE 0

typedef struct ClientNode 
{
    pid_t client_pid;
    char *status;
    struct ClientNode *next;
} ClientNode;

typedef struct PoolNode
{
    int value;
    int status;  // 1 = in used, 0 = free
    ClientNode *current_client;
    struct LList *client_list;
    struct PoolNode *next;
} PoolNode;


LList *pool_list;

// ClientNode Operators
ClientNode * ClientNode_create(pid_t client_pid, char *status);

// PoolNode operators
PoolNode * PoolNode_create(int value, ClientNode *client);
PoolNode * PoolNode_search(LList *llist, int value);
int PoolNode_has_value(LList *llist, int value);

// Other operator
void PoolList_print(LList *llist);
void ClientList_print(ClientNode *client_node);

#endif