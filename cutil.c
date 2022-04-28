#include "cutil.h"
#include <string.h>

void* (*cu_malloc)(size_t);
void* (*cu_realloc)(void*, size_t);
void (*cu_free)(void*) = CUTIL_FREE;
void* (*cu_memset)(void*,int,size_t);
void* (*cu_memcpy)(void*,const void*,size_t);
void* (*cu_memmove)(void*,const void*,size_t);

void cutil_init()
{
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
