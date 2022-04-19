#include "array.h"
#include "cutil.h"

void array_init(array_t* array, uint size, uint align)
{
    array->mem = NULL;
    array->size = size;
    array->count = 0;
    array->align = align;
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

uint array_align(array_t* array, uint count)
{
    return cu_align(count, array->align);
}

void array_resize(array_t* array, uint newCount)
{
    if (array->count % array->align)
    {
        array->count = newCount;
    }
    else
    {
        size_t size = array_align(array, newCount)*array->size;
        if (array->count) array->mem = cu_realloc(array->mem, size);
        else array->mem = cu_malloc(size);
        array->count = array->mem ? newCount : 0;
    }
}

void array_push(array_t* array, const void* data)
{
    array_resize(array, array->count + 1);
    cu_memcpy(array_last(array), data, array->size);
}

void array_pop(array_t* array, void* src)
{
    if (array->count)
    {
        if (src) cu_memcpy(src, array_last(array), array->size);
        array_resize(array, array->count - 1);
    }
}

void array_insert(array_t* array, uint idx, const void* data)
{
    array_resize(array, array->count + 1);
    uint move = array->count - idx - 1;
    if (move)
    {
        cu_memmove(array_at(array, idx + 1),
            array_at(array, idx), move*array->size);
    }
    cu_memcpy(array_at(array, idx), data, array->size);
}

void array_remove(array_t* array, uint idx)
{
    uint move = array->count - idx - 1;
    if (move)
    {
        cu_memmove(array_at(array, idx),
            array_at(array, idx + 1), move*array->size);
    }
    array_resize(array, array->count - 1);
}
