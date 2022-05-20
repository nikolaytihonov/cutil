#ifndef __CUTIL_VA_LIST_H
#define __CUTIL_VA_LIST_H

#include "cutypes.h"

#if (CU_ARCH == x86_64)
#   define VA_NUM   6
#elif (CU_ARCH == AARCH64)
#   define VA_NUM   8
#elif (defined(CU_ARCH_ARM7))
#   define  VA_NUM  4
#else
#   define VA_NUM   0
#endif

typedef struct {
    uword args[VA_NUM];
} cu_va_list;

extern void cu_va_start(cu_va_list* va);
extern uword cu_va_arg(cu_va_list* va, unsigned idx);

#endif