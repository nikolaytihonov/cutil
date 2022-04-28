#ifndef __CUTYPES_H
#define __CUTYPES_H

#include <stddef.h>
#include <stdint.h>

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

#if defined(__x86_64__) || defined(_M_X64)
#   define CU_ARCH x86_64
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#   define CU_ARCH x86_32
#elif defined(__ARM_ARCH_2__)
#   define CU_ARCH ARM2
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
#   define CU_ARCH ARM3
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
#   define CU_ARCH ARM4T
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
#   define CU_ARCH ARM5
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
#   define CU_ARCH ARM6T2
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
#   define CU_ARCH ARM6
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#   define CU_ARCH ARM7
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#   define CU_ARCH ARM7A
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#   define CU_ARCH ARM7R
#elif defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
#   define CU_ARCH ARM7M
#elif defined(__ARM_ARCH_7S__)
#   define CU_ARCH ARM7S
#elif defined(__aarch64__) || defined(_M_ARM64)
#   define CU_ARCH AARCH64
#elif defined(mips) || defined(__mips__) || defined(__mips)
#   define CU_ARCH MIPS
#elif defined(__sh__)
#   define CU_ARCH SUPERH
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
#   define CU_ARCH POWERPC
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
#   define CU_ARCH POWERPC64
#elif defined(__sparc__) || defined(__sparc)
#   define CU_ARCH SPARC
#elif defined(__m68k__)
#   define CU_ARCH M68K
#else
#   define CU_ARCH ARCH_UNKNOWN;
#endif

#if (CU_ARCH == x86_64 || CU_ARCH == AARCH64 || CU_ARCH == POWERPC64)
#   define CU_64BIT
#else
#   define CU_32BIT
#endif

#if defined(CU_64BIT)
#   define CU_WORD_BITS 64
#   define CU_WORD_POW2 6
typedef uint64_t uword;
typedef int64_t iword;
#elif defined(CU_32BIT)
#   define CU_WORD_BITS 32
#   define CU_WORD_POW2 5
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