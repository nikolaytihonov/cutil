#include "cutil.h"
#include "endian.h"

#ifdef CUTIL_NOSTDLIB
void* (*cu_malloc)(size_t) = NULL;
void* (*cu_realloc)(void*, size_t) = NULL;
void (*cu_free)(void*) = NULL;
void* (*cu_memset)(void*,int,size_t) = _cu_memset;
void* (*cu_memcpy)(void*,const void*,size_t) = _cu_memcpy;
void* (*cu_memmove)(void*,const void*,size_t) = _cu_memmove;
void* (*cu_memcmp)(const void*,const void*, size_t) = _cu_memcmp;
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
#endif

void cutil_init()
{
    cu_endian_init();
}

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
