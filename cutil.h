#ifndef __CUTIL_H
#define __CUTIL_H

#include "cutypes.h"
#include <stdlib.h>

enum cu_arch_e {
    ARCH_UNKNOWN = 0,
    x86_64,
    x86_32,
    ARM2,
    ARM3,
    ARM4T,
    ARM5,
    ARM6T2,
    ARM6,
    ARM7,
    ARM7A,
    ARM7R,
    ARM7M,
    ARM7S,
    AARCH64,
    MIPS,
    SUPERH,
    POWERPC,
    POWERPC64,
    SPARC,
    M68K,
};

enum cu_arch_e cutil_arch();

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

#endif