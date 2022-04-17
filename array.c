#include "array.h"
#include "cutil.h"

void array_init(array_t* array, uint size, uint align)
{
    array->mem = NULL;
    array->size = size;
    array->count = 0;
    array->align = align;
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

static uint array_align(array_t* array, uint count)
{
    return (count / array->align + !!(count % array->align)) * array->align;
}

void array_push(array_t* array, const void* data)
{
    if (!(array->count % array->align))
        array_alloc(array, array->count + 1);
    else array->count++;
    cu_memcpy(array_last(array), data, array->size);
}

void array_pop(array_t* array, void* src)
{

}