#ifndef __VA_LIST_H
#define __VA_LIST_H

#include "cutypes.h"

#if (CU_ARCH == x86_64)
#   define VA_NUM   6
#else
#   define VA_NUM   0
#endif

typedef struct {
    uword args[VA_NUM];
} cu_va_list;

extern void cu_va_start(cu_va_list* va);
extern uword cu_va_arg(cu_va_list* va, unsigned idx);

#endif