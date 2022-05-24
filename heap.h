#ifndef __CUTIL_HEAP_H
#define __CUTIL_HEAP_H

#include "cutypes.h"

typedef struct {
    void* start;
    uword size;
} mheap_t;

typedef struct {
    void* prev;
    uword size;
} mblock_t;

#define MBLOCK_ALLOCATED    (1<<0)
#define MBLOCK_SIZE(size)   ((size) & ~MBLOCK_ALLOCATED)

#ifdef CU_64BIT
#   define  MBLOCK_ALIGN    4
#else
#   define  MBLOCK_ALIGN    3
#endif

void heap_init(mheap_t* heap, void* start, uword size);
void heap_split(mblock_t* block, uword size);
void heap_join(mblock_t* block, mblock_t* other);
mblock_t* heap_alloc(mheap_t* heap, uword _size);
void heap_free(mheap_t* heap, mblock_t* block);
mblock_t* heap_realloc(mheap_t* heap, mblock_t* block, uword _size);

#endif