#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

int main()
{
    list_t list;
    list_init(&list);

    srand(time(NULL));
    for (uint i = 0; i < 5; i++)
    {
        uint num = i;//rand();
        list_add(&list, sizeof(uint), &num);
    }
    list_remove(&list, list_at(&list, 2));

    CU_LIST_FOREACH(&list)
    {
        printf("%p\t%p\t%p\t%d\n", i->prev, i, i->next,
            LIST_NODE_VALUE(i, uint));
    }

    list_clear(&list);
    return 0;
}