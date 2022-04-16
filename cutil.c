#include "cutil.h"

void* (*cu_malloc)(size_t) = CUTIL_MALLOC;
void* (*cu_relloac)(void*, size_t) = CUTIL_REALLOC;
void* (*cu_free)(void*) = CUTIL_FREE;
