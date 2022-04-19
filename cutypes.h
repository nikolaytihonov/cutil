#ifndef __CUTYPES_H
#define __CUTYPES_H

#include <stddef.h>
#include <stdint.h>

typedef unsigned int uint;
#define CU_UINT_SIZE sizeof(uint)

typedef void* cu_ptr;
#define CU_PTR_SIZE sizeof(cu_ptr)

#define cu_align(value, align) (((value / align) + !!(value % align))*align)

#endif