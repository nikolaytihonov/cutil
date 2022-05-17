#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "cutil.h"
#include "list.h"
#include "array.h"
#include "bitmap.h"
#include "endian.h"
#include "struct.h"
#include "va_list.h"
#include "string.h"

typedef uint8_t item_t[14];

struct test_s {
    uint8_t seq[6];
    uint32_t array1[12];
    uint16_t count;
    item_t array2[5];
    uint64_t value;
    char text[32];
} __attribute__((packed)) test = {
    .seq = {0},
    .array1 = {0},
    .count = 5,
    .value = 123456789,
    .text = "Hello World"
};

CU_STRUCT_BEGIN(test_s, LittleEndian)
CU_VALUE_SEQUENCE(6)
CU_VALUE_ARRAY(4, 12)
CU_VALUE_INT16()
CU_VALUE_ARRAY_INDEX(14, 2)
CU_VALUE_INT64()
CU_VALUE_ARRAY_ZERO(sizeof(char))
CU_STRUCT_END()

void va_test(int fixed, ...)
{
    cu_va_list va;
    cu_va_start(&va);
    
    printf("va_test\n");
    for (unsigned i = 0; i < 6; i++)
        printf("\t%lu\n", cu_va_arg(&va, i));
}

int main()
{
    cu_malloc = malloc;
    cu_realloc = realloc;
    cu_free = free;

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

    uint val3[5] = {1, 2, 3, 4, 0};
    uint val4[5];

    _cu_memcpy(val4, val3, sizeof(val3));
    cu_memzero(val3, sizeof(val3));
    printf("cu_memzero test\t%p\n", cu_memtest(val3, sizeof(val3)));
    printf("val4 values\n");
    for (unsigned i = 0; i < 5; i++)
        printf("\t%u\n", val4[i]);
    printf("\n");
    
    void* dst = &val4[1];
    void* src = &val4[0];
    printf("memmove delta\t%lx\n", (uintptr_t)dst - (uintptr_t)src);
    _cu_memmove(dst, src, sizeof(uint) * 3);
    printf("val4 memmove ->\n");
    for (unsigned i = 0; i < 5; i++)
        printf("\t%u\n", val4[i]);
    printf("\n");

    printf("[endian]\n");
    printf("cutil_endian\t%u\n", cu_endian);
    printf("%x\t%x\n", 0x1234, cu_bswap16(0x1234));
    printf("%x\t%x\n", 0x12345678, cu_bswap32(0x12345678));
    printf("%lx\t%lx\n", 0x12345678abcd8765, cu_bswap64(0x12345678abcd8765));

    printf("[struct]\n");
    printf("value_offset\t%u\n", value_offset(CU_STRUCT(test_s), 4, &test));
    printf("value_size\t%u\n", value_size(CU_STRUCT(test_s), 4, &test));
    uint64_t value;
    value_get(CU_STRUCT(test_s), 4, &test, &value);
    printf("value\t%u\n", value);
    printf("struct_size\t%u\t%u\n", sizeof(struct test_s),
        struct_size(CU_STRUCT(test_s), &test));
    printf("value_offset\t%u\n", value_offset(CU_STRUCT(test_s), 5, &test));
    printf("value_size\t%u\n", value_size(CU_STRUCT(test_s), 5, &test));

    printf("[va_list]\n");
    va_test(1337, 1, 2, 3, 4, 5);

    printf("[string]\n");
    printf("cu_memcmp\t%u\n", cu_memcmp(val3, val3, sizeof(val3)));
    
    const char* str1 = "Hello World!";
    char str2[32] = {0};
    cu_strcpy(str2, str1);
    printf("cu_strcpy\tstr2\t\"%s\"\n", str2);
    printf("cu_strcmp\t%u\n", cu_strcmp(str2, str1));

    char str3[64] = {0};
    cu_sprintf(str3, 64, "hello %u world \"%s\"", 2312, "test");
    printf("cu_sprintf\t%s\n", str3);

    const char* str4 = "\"test\" 2312";
    char str5[8] = {0};
    iword val5 = 0;
    cu_sscanf((char*)str4, "\"%s\" %d", str5, 8, &val5);
    printf("cu_sscanf\t%s\t%u\n", str5, val5);

    cutil_exit();
    return 0;
}
