#include "cutil.h"
#include <string.h>

enum cu_arch_e cutil_arch()
{
#if defined(__x86_64__) || defined(_M_X64)
    return x86_64;
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
    return x86_32;
#elif defined(__ARM_ARCH_2__)
    return ARM2;
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
    return ARM3;
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
    return ARM4T;
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
    return ARM5;
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
    return ARM6T2;
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
    return ARM6;
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    return ARM7;
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    return ARM7A;
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    return ARM7R;
#elif defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    return ARM7M;
#elif defined(__ARM_ARCH_7S__)
    return ARM7S;
#elif defined(__aarch64__) || defined(_M_ARM64)
    return ARM64;
#elif defined(mips) || defined(__mips__) || defined(__mips)
    return MIPS;
#elif defined(__sh__)
    return SUPERH;
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
    return POWERPC;
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
    return POWERPC64;
#elif defined(__sparc__) || defined(__sparc)
    return SPARC;
#elif defined(__m68k__)
    return M68K;
#else
    return ARCH_UNKNOWN;
#endif
}

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
