#include "cutil.h"
#include "endian.h"

#ifdef CUTIL_NOSTDLIB
#   include "heap.h"
mheap_t cu_heap;

void* _cu_malloc(size_t size)
{
    mblock_t* block =  heap_alloc(&cu_heap, size);
    return block ? (u8*)block + sizeof(mblock_t) : NULL;
}

void* _cu_realloc(void* mem, size_t size)
{
    mblock_t* block = heap_realloc(&cu_heap,
        (mblock_t*)((u8*)mem - sizeof(mblock_t)), size);
    return block ? (u8*)block + sizeof(mblock_t) : NULL;
}

void _cu_free(void* mem)
{
    return heap_free(&cu_heap, (mblock_t*)((u8*)mem - sizeof(mblock_t)));
}

void* (*cu_malloc)(size_t) = _cu_malloc;
void* (*cu_realloc)(void*, size_t) = _cu_realloc;
void (*cu_free)(void*) = _cu_free;
void* (*cu_memset)(void*,int,size_t) = _cu_memset;
void* (*cu_memcpy)(void*,const void*,size_t) = _cu_memcpy;
void* (*cu_memmove)(void*,const void*,size_t) = _cu_memmove;
void* (*cu_memcmp)(const void*,const void*, size_t) = _cu_memcmp;

void cutil_init(void* heap, size_t size)
{
    heap_init(&cu_heap, heap, size);
    cu_endian_init();
}
#else
#   include <stdlib.h>
#   include <string.h>

void* (*cu_malloc)(size_t) = malloc;
void* (*cu_realloc)(void*, size_t) = realloc;
void (*cu_free)(void*) = free;
void* (*cu_memset)(void*,int,size_t) = memset;
void* (*cu_memcpy)(void*,const void*,size_t) = memcpy;
void* (*cu_memmove)(void*,const void*,size_t) = memmove;
void* (*cu_memcmp)(const void*,const void*, size_t) = memcmp;

void cutil_init(void* heap, size_t size)
{
    cu_endian_init();
}
#endif

void cutil_exit()
{
}

void __cu_memmove(void* dst, void* src, size_t size)
{
    if (dst > src)
    {
        uint d = (uword)dst - (uword)src;
        src = (u8*)src + size;
        dst = (u8*)dst + size; 
        while (size)
        {
            src = (u8*)src - d;
            dst = (u8*)dst - d;
            cu_memcpy(dst, src, d);
            size -= d; 
        }
    }
    else if (dst < src)
    {
        uint d = (uword)src - (uword)dst;
        while (size)
        {
            cu_memcpy(dst, src, d);
            src = (u8*)src + d;
            dst = (u8*)dst + d;
            size -= d;
        }
    }
}
