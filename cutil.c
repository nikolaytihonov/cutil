#include "cutil.h"
#include <string.h>

void* (*cu_malloc)(size_t) = CUTIL_MALLOC;
void* (*cu_realloc)(void*, size_t) = CUTIL_REALLOC;
void (*cu_free)(void*) = CUTIL_FREE;
void* (*cu_memset)(void*,int,size_t) = CUTIL_MEMSET;
void* (*cu_memcpy)(void*,const void*,size_t) = CUTIL_MEMCPY;
void* (*cu_memmove)(void*,const void*,size_t) = CUTIL_MEMMOVE;
