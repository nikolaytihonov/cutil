#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "array.h"
#include "bitmap.h"

int main()
{
    printf("[list]\n");
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

    printf("[array]\n");
    array_t array;
    array_init(&array, sizeof(uint), 2);
    printf("%p\t%d\t%d\t%d\n", array.mem,
        array.size, array.count, array.align);

    for (uint i = 0; i < 5; i++)
    {
        uint num = i;
        array_push(&array, &i);
    }
    uint num = 42;
    array_remove(&array, 0);
    array_insert(&array, 1, &num);

    CU_ARRAY_FOREACH(&array)
    {
        uint8_t* ptr = array_at(&array, i);
        printf("%p\t%d\n", ptr, *(uint*)ptr);
    }

    printf("%p\t%d\t%d\t%d\n", array.mem,
        array.size, array.count, array.align);
    array_clear(&array);

    printf("[bitmap]\n");
    printf("bit_align2\t%u\n", bit_align2(354, 3));
    printf("bit_log2\t%u\n", bit_log2(34));
    return 0;
}