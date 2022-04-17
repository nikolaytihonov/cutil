#include "array.h"
#include "cutil.h"

array_t* array_create(uint size, uint align, uint reserve)
{
    uint capacity = reserve
        ? (reserve / align + !!(reserve % align)) * align
        : align;
    array_t* array = (array_t*)cu_malloc(CU_ARRAY_HEAD_SIZE + capacity*size);
    if (!array) return NULL;

    array->size = size;
    array->count = 0;
    array->align = align;
    return array;
}

void array_delete(array_t* array)
{
    cu_free(array);
}

void* array_push(array_t* array, const void* data)
{
    
}
