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
        uint num = rand();
        list_add(&list, sizeof(uint), &num);
    }

    CU_LIST_FOREACH(&list)
    {
        printf("%p\t%d\n", i, LIST_NODE_VALUE(i, uint));
    }

    list_clear(&list);
    return 0;
}