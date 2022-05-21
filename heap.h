#ifndef __CUTIL_HEAP_H
#define __CUTIL_HEAP_H

#include "cutypes.h"

typedef struct mblock_s {
    struct mblock_s* prev;
    struct mblock_s* next;
    uword size;
    u8 data[1];
} mblock_t;

typedef struct {
    u8* data;
    uword size;
} mheap_t;

#define MBLOCK_SIZE             (CU_WORD_SIZE*3)
#define MBLOCK_SIZE_MASK        ((CU_WORD_BITS/8) - 1)
#define MBLOCK_ALIGN_SIZE(size) ((size) & ~MBLOCK_SIZE_MASK)
#define MBLOCK_ATTR_ALLOC       (1<<0)
#define IS_MBLOCK_ALLOC(mblock) (mblock->size & MBLOCK_ATTR_ALLOC)

#ifdef CU_64BIT
#   define  MBLOCK_ALIGN    5
#else
#   define  MBLOCK_ALIGN    4
#endif

void heap_init(mheap_t* heap, void* data, uword size);
void heap_join(mblock_t* start, int dir);
void heap_split(mblock_t* block, size_t req_size);
void* heap_alloc(mheap_t* heap, size_t size);
void* heap_realloc(mheap_t* heap, void* mem, size_t size);
void heap_free(mheap_t* heap, void* mem);

#endif