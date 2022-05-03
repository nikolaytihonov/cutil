#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cutil.h"
#include "list.h"
#include "array.h"
#include "bitmap.h"
#include "endian.h"
#include "struct.h"

typedef uint8_t item_t[14];

struct test_s {
    uint8_t seq[6];
    uint32_t array1[12];
    uint16_t count;
    item_t array2[5];
    uint64_t value;
} __attribute__((packed)) test = {
    .seq = {0},
    .array1 = {0},
    .count = 5,
    .value = 123456789
};

CU_STRUCT_BEGIN(test_s, LittleEndian)
CU_VALUE_SEQUENCE(6)
CU_VALUE_ARRAY(4, 12)
CU_VALUE_INT16()
CU_VALUE_ARRAY_INDEX(14, 2)
CU_VALUE_INT64()
CU_STRUCT_END()

int main()
{
    cutil_init();
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

    printf("[cutypes]\n");
    printf("uword\t%u\n", sizeof(uword) * 8);
    printf("uint\t%u\n", sizeof(uint) * 8);

    printf("[bitmap]\n");
    printf("bit_align2\t%u\n", bit_align2(354, 3));
    printf("bit_log2\t%u\n", bit_log2(34));
    num = 5;
    bit_set(num, 1, 1);
    printf("bit_get\t%u\n", bit_get(num, 0));
    printf("num\t%u\n", num);
    bitmap(m, 128);
    bitmap_set(m, 0, 1);
    bitmap_set(m, 5, 1);
    bitmap_set(m, 64, 1);
    printf("bitmap\t%u\t%u\n", m[0], m[1]);
    printf("bitmap\t%u\t%u\n", bitmap_get(m, 0), bitmap_get(m, 64));
    bitmap_set(m, 5, 0);
    printf("bitmap\t%u\n", bitmap_get(m, 5));

    printf("[cutil]\n");
    printf("cutil_arch\t%u\n", CU_ARCH);
    uint64_t val1 = 0;
    printf("val1\t%u\tcu_memtest\t%p\n", val1, cu_memtest(&val1, sizeof(val1)));
    char val2[] = {0,0,0,1,0,0,0,0,0,0,4,0,0};
    printf("val2\tcu_memtest\t%p\n", cu_memtest(val2, sizeof(val2)));

    printf("[endian]\n");
    printf("cutil_endian\t%u\n", cu_endian);
    printf("%x\t%x\n", 0x12345678, l32toh32(0x12345678));
    printf("%lx\t%lx\n", 0x12345678abcd8765, h64ton64(0x12345678abcd8765));

    printf("[struct]\n");
    printf("value_offset\t%u\n", value_offset(CU_STRUCT(test_s), 4, &test));
    printf("value_size\t%u\n", value_size(CU_STRUCT(test_s), 4, &test));
    uint64_t value;
    value_get(CU_STRUCT(test_s), 4, &test, &value);
    printf("value\t%u\n", value);
    printf("struct_size\t%u\t%u\n", sizeof(struct test_s),
        struct_size(CU_STRUCT(test_s), &test));

    cutil_exit();
    return 0;
}