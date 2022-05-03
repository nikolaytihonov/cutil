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

const void* cu_memtest(const void* mem, uint size)
{
    unsigned i;
    for (i = 0; i < size / sizeof(uword); i++)
    {
        if (*(uword*)mem) return mem;
        *(uword*)mem++;
    }

    for (i = 0; i < size % sizeof(uword); i++)
    {
        if (*(uint8_t*)mem) return mem;
        *(uint8_t*)mem++;
    }

    return NULL;
}
