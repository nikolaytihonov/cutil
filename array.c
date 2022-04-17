#include "array.h"
#include "cutil.h"

void array_init(array_t* array, uint size, uint align, uint reserve)
{
    uint capacity = reserve
        ? (reserve / align + !!(reserve % align)) * align
        : align;
    array->size = size;
    array->count = 0;
    array->align = align;
    array_alloc(array, capacity);
}

void array_alloc(array_t* array, uint newCount)
{
    size_t size = newCount*array->size;
    if (array->count) array->mem = cu_realloc(array->mem, size);
    else array->mem = cu_malloc(size);
    array->count = array->mem ? newCount : 0;
}

void array_clear(array_t* array)
{
    if (array->count)
    {
        cu_free(array->mem);
        array->mem = NULL;
        array->count = 0;
    }
    array->size = 0;
    array->align = 0;
}
