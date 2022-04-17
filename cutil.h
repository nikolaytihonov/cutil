#ifndef __CUTIL_H
#define __CUTIL_H

#include "cutypes.h"
#include <stdlib.h>

#define CUTIL_MALLOC malloc
#define CUTIL_REALLOC realloc
#define CUTIL_FREE free
#define CUTIL_MEMSET memset
#define CUTIL_MEMCPY memcpy
#define CUTIL_MEMMOVE memmove

extern void* (*cu_malloc)(size_t);
extern void* (*cu_realloc)(void*, size_t);
extern void (*cu_free)(void*);
extern void* (*cu_memset)(void*,int,size_t);
extern void* (*cu_memcpy)(void*,const void*,size_t);
extern void* (*cu_memmove)(void*,const void*,size_t);

#endif