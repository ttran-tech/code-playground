#ifndef POOL_H
#define POOL_H

typedef struct ClientNode 
{
    int client_id;
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

LList * llist_init();
PoolNode * create_new_node(int value, ClientNode *client);

#endif