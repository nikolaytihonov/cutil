#ifndef __CUTIL_H
#define __CUTIL_H

#include "cutypes.h"
#include <stdlib.h>

extern void* _cu_memset(void* dst, int val, size_t size);
extern void* _cu_memcpy(void* dst, const void* src, size_t size);

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

void cutil_init();
void cutil_exit();

extern const void* cu_memtest(const void* mem, uint size);
extern void cu_memzero(void* dst, size_t size);

void _cu_memmove(void* dst, void* src, size_t size);

#endif