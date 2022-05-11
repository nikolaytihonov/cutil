#include "cutil.h"
#include "endian.h"
#include <string.h>

void* (*cu_malloc)(size_t);
void* (*cu_realloc)(void*, size_t);
void (*cu_free)(void*) = CUTIL_FREE;
void* (*cu_memset)(void*,int,size_t);
void* (*cu_memcpy)(void*,const void*,size_t);
void* (*cu_memmove)(void*,const void*,size_t);

void cutil_init()
{
    cu_endian_init();

    cu_malloc = CUTIL_MALLOC;
    cu_realloc = CUTIL_REALLOC;
    cu_free = CUTIL_FREE;
    cu_memset = CUTIL_MEMSET;
    cu_memcpy = CUTIL_MEMCPY;
    cu_memmove = CUTIL_MEMMOVE;
}

void cutil_exit()
{
}

void _cu_memmove(void* dst, void* src, size_t size)
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
