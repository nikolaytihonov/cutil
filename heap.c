#include "heap.h"
#include "cutil.h"

void heap_init(mheap_t* heap, void* start, uword size)
{
    heap->start = start;
    heap->size = size;

    mblock_t* block = (mblock_t*)heap->start;
    block->prev = NULL;
    block->size = size;
}

void heap_split(mblock_t* block, uword size)
{
    mblock_t* split = (mblock_t*)((u8*)block + size);
    split->prev = block;
    split->size = block->size - size;
    block->size = size;
}

void heap_join(mblock_t* block, mblock_t* other)
{
    if (block < other)
    {
        mblock_t* next = (mblock_t*)((u8*)other + other->size);
        next->prev = block;
        block->size += other->size;
    }
    else if (block > other)
    {
        mblock_t* next = (mblock_t*)((u8*)block + block->size);
        next->prev = other;
        other->size += block->size;
    }
}

mblock_t* heap_alloc(mheap_t* heap, uword _size)
{
    uword size = cu_round2_up(_size + sizeof(mblock_t), MBLOCK_ALIGN);
    mblock_t* block = (mblock_t*)((u8*)heap->start);
    mblock_t* end = (mblock_t*)((u8*)heap->start + heap->size);
    while ((block->size & MBLOCK_ALLOCATED) || MBLOCK_SIZE(block->size) < size)
    {
        block = (mblock_t*)((u8*)block + MBLOCK_SIZE(block->size));
        if (block >= end) return NULL;
    }

    if (block->size > size)
    {
        heap_split(block, size);
    }

    block->size |= MBLOCK_ALLOCATED;
    return block;
}

void heap_free(mheap_t* heap, mblock_t* block)
{
    block->size &= ~MBLOCK_ALLOCATED;
    mblock_t* prev = block->prev;
    mblock_t* next = (mblock_t*)((u8*)block + block->size);
    mblock_t* end = (mblock_t*)((u8*)heap->start + heap->size);
    if (prev && !(prev->size & MBLOCK_ALLOCATED))
        heap_join(block, prev);
    if (next < end && !(next->size & MBLOCK_ALLOCATED))
        heap_join(block, next);
}

mblock_t* heap_realloc(mheap_t* heap, mblock_t* block, uword _size)
{
    block->size &= ~MBLOCK_ALLOCATED;
    uword size = cu_round2_up(_size + sizeof(mblock_t), MBLOCK_ALIGN);
    mblock_t* next = (mblock_t*)((u8*)block + block->size);
    mblock_t* new;
    if (!(next->size & MBLOCK_ALLOCATED) && next->size >= size)
    {
        new = block;
        heap_join(new, next);
        heap_split(new, size);
        new->size |= MBLOCK_ALLOCATED;
    }
    else
    {
        heap_free(heap, block);
        new = heap_alloc(heap, size);
        if (new)
        {
            cu_memcpy((u8*)new + sizeof(mblock_t),
                (u8*)block + sizeof(mblock_t), size - sizeof(mblock_t));
        }
    }
    return new;
}
