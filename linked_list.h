#ifndef _MY_LINKED_LIST
#define _MY_LINKED_LIST 1
#include <stdlib.h>

typedef struct list_t
{
    int size;
    struct node_t*head;
} list_t;

typedef struct node_t
{
    void *data;
    struct node_t *next;
} node_t;

list_t *create_list()
{
    list_t *list=(list_t*)calloc(1,sizeof(list_t));
    return list;
}
int list_insert(list_t *list,void *data)
{
    node_t *new_node=NULL;
    if(list==NULL)return 0;
    new_node=(node_t*)calloc(1,sizeof(new_node));
    if(new_node==NULL)return 0;
    new_node->data=data;
    new_node->next=list->head;
    list->head=new_node;
    list->size++;
    return 1;
}
#endif
