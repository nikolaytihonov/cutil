#ifndef __CUTIL_H
#define __CUTIL_H

#include "cutypes.h"
#include <stdlib.h>

#define CUTIL_MALLOC malloc
#define CUTIL_REALLOC realloc
#define CUTIL_FREE free

extern void* (*cu_malloc)(size_t);
extern void* (*cu_realloc)(void*, size_t);
extern void* (*cu_free)(void*);

#endif