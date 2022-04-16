#ifndef __LIST_H
#define __LIST_H

#include "cutypes.h"

typedef struct list_node_s {
    struct list_node_s* prev;
    struct list_node_s* next;
    uint8_t data[1];
} list_node_t;

#define LIST_NODE_SIZE (CU_PTR_SIZE * 2)
#define LIST_NODE_PTR(data) ((uint8_t*)data - LIST_NODE_SIZE)
#define LIST_NODE_DATA(node) ((uint8_t*)node + LIST_NODE_SIZE)
#define LIST_NODE_VALUE(node, type) (*(type*)LIST_NODE_DATA(node))

typedef struct {
    list_node_t* first;
    list_node_t* last;
    uint count;
} list_t;

void list_init(list_t* list);
void list_clear(list_t* list);

void list_add(list_t* list, uint size, void* data);
void list_remove(list_t* list, list_node_t* node);
list_node_t* list_at(list_t* list, uint idx);

#define CU_LIST_FOREACH(list)  \
    for(list_node_t* i = (list)->first; i; i = i->next)

#endif