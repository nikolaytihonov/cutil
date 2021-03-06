#include "list.h"
#include "cutil.h"
#include <string.h>

void list_init(list_t* list)
{
    list->first = NULL;
    list->last = NULL;
    list->count = 0;
}

void list_clear(list_t* list)
{
    list_node_t* node = list->first;
    if (node)
    {
        list_node_t* next;
        do {
            next = node->next;
            cu_free(node);
        } while (node = next);
    }
    list->first = NULL;
    list->last = NULL;
    list->count = 0;
}

void list_add(list_t* list, uint size, void* data)
{
    uint nodeSize = LIST_NODE_SIZE + size;
    list_node_t* node = (list_node_t*)cu_malloc(nodeSize);
    cu_memset(node, '\0', nodeSize);
    if (data)
    {
        cu_memcpy((u8*)node + LIST_NODE_SIZE, data, size);
    }

    list_node_t* last = list->last;
    if (!list->first) list->first = node;
    if (last)
    {
        last->next = node;
        node->prev = last;
    }
    list->last = node;
    list->count++;
}

void list_remove(list_t* list, list_node_t* node)
{
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (list->first == node) list->first = node->next;
    if (list->last == node) list->last == node->prev;
    list->count--;
    cu_free(node);
}

list_node_t* list_at(list_t* list, uint idx)
{
    list_node_t* node = list->first;
    if (!idx) return node;
    else if (idx >= list->count) return NULL;
    while (idx--) node = node->next;
    return node;
}
