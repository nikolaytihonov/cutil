#ifndef __CUTYPES_H
#define __CUTYPES_H

#include <stddef.h>
#include <stdint.h>

#define ARCH_UNKNOWN    0
#define x86_64          1
#define x86_32          2
#define ARM2            3
#define ARM3            4
#define ARM4T           5
#define ARM5            6
#define ARM6T2          7
#define ARM6            8
#define ARM7            9
#define ARM7A           10
#define ARM7R           11
#define ARM7M           12
#define ARM7S           13
#define AARCH64         14
#define MIPS            15
#define SUPERH          16
#define POWERPC         17
#define POWERPC64       18
#define SPARC           19
#define M68K            20

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

#if (CU_ARCH == x86_64 || CU_ARCH == x86_32)
#   define CU_ARCH_X86
#elif (CU_ARCH >= ARM2 && CU_ARCH <= AARCH64)
#   define CU_ARCH_ARM
#   define CU_ARCH_ARM_ARCH __ARM_ARCH
#elif (CU_ARCH == MIPS)
#   define CU_ARCH_MIPS
#elif (CU_ARCH == SUPERH)
#   define CU_ARCH_SUPERH
#elif (CU_ARCH == POWERPC || CU_ARCH == POWERPC64)
#   define CU_ARCH_POWERPC
#elif (CU_ARCH == SPARC)
#   define CU_ARCH_SPARC
#elif (CU_ARCH == M68K)
#   define CU_ARCH_M68K
#else
#   warning "unknown architecture"
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
#   warning "unknown bus width for arch " CU_ARCH
#endif

typedef uint32_t uint;
#define CU_UINT_SIZE sizeof(uint)

typedef void* cu_ptr;
#define CU_PTR_SIZE sizeof(cu_ptr)

#define cu_align(value, align) (((value / align) + !!(value % align))*align)

#endif