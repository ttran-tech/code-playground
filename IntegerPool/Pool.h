#ifndef POOL_H
#define POOL_H

#define IN_USE 1
#define FREE 0

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
    size_t size;
} LList;

LList *pool_list;

// ClientNode Operators
ClientNode * create_client_node(pid_t client_pid);

// PoolNode operators
PoolNode * create_pool_node(int value, ClientNode *client);

// LList operators
LList * llist_init();
int llist_is_empty(LList *llist);
PoolNode * llist_search_by_value(LList *llist, int value);


// Other operator
void print_pool_list(LList *llist);
void print_client_list(ClientNode *client_node);
#endif