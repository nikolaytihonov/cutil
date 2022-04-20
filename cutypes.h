#ifndef __CUTYPES_H
#define __CUTYPES_H

#include <stddef.h>
#include <stdint.h>

#if (!defined(CU_64BIT) && !defined(CU_32BIT))
#   define CU_64BIT
#endif

#if defined(CU_64BIT)
#define CU_WORD_BITS 64
#define CU_WORD_POW2 6
typedef uint64_t uword;
typedef int64_t iword;
#elif defined(CU_32BIT)
#define CU_WORD_BITS 32
#define CU_WORD_POW2 5
typedef uint32_t uword;
typedef int32_t iword;
#else
#   warning "define CU_32BIT or CU_64BIT"
#endif

typedef uint32_t uint;
#define CU_UINT_SIZE sizeof(uint)

typedef void* cu_ptr;
#define CU_PTR_SIZE sizeof(cu_ptr)

#define cu_align(value, align) (((value / align) + !!(value % align))*align)

#endif