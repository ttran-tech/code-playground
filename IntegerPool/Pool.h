#ifndef POOL_H
#define POOL_H

typedef struct ClientNode 
{
    pid_t client_pid;
    struct ClientNode *next;
} ClientNode;

typedef struct PoolNode
{
    int value;
    int is_in_use;  // 1 = in used, 0 = free
    ClientNode *client;
    struct PoolNode *next;
} PoolNode;

typedef struct LList
{
    void *head;
    void *tail;
    size_t list_size;
} LList;

LList *pool_list;

// ClientNode Operators
ClientNode * create_client_node(pid_t client_pid);

// PoolNode operators
PoolNode * create_new_node(int value, ClientNode *client);

// LList operators
LList * llist_init();
int llist_is_empty(LList *llist);

#endif