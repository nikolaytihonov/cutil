#include "heap.h"

static mblock_t* mblock_get_next(mblock_t* block)
{
    return (mblock_t*)((u8*)block+(block->size & ~7));
}

static mblock_t* mblock_by_data(void* data)
{
    return (mblock_t*)((u8*)data - MBLOCK_SIZE);
}

static u64 mblock_get_size(mblock_t* block)
{
    return block->size & ~7;
}

void heap_init(mheap_t* heap, void* data, uword size)
{
    heap->data = data;
    heap->size = size;
}

void heap_join(mblock_t* start, int dir)
{
    mblock_t* cur;
    u64 blk_size;
    
    blk_size = 0;
    cur = start;
    while(cur != NULL && !IS_MBLOCK_ALLOC(cur))
    {
        blk_size += mblock_get_size(cur);
        cur->size = 0;
        if(dir > 0) cur = cur->next;
        else if(dir < 0) cur = cur->prev;
    }
    
    if(dir > 0)
    {
        start->next = cur;
        start->size = blk_size & ~7;
        if(cur)
        {
            if(cur->next) cur->next->prev = start;
        }
    }
    else if(dir < 0)
    {
        if(cur)
        {
            cur = cur->next;
            cur->size = blk_size & ~7;
            cur->next = start->next;
        }
    }
}

void heap_split(mblock_t* block, size_t req_size)
{
    size_t tot_size = mblock_get_size(block);
    mblock_t* split;
    
    block->size = (req_size)|MBLOCK_ATTR_ALLOC;
    split = mblock_get_next(block);
    
    //Init prev and next
    split->prev = block;
    split->next = block->next;
    block->next = split;
    
    split->size = (tot_size-req_size) & ~7;
}

void* heap_alloc(mheap_t* heap, size_t size)
{
    mblock_t* start,*block,*prev;
    size = cu_round2_up((size + MBLOCK_SIZE), MBLOCK_ALIGN);
    
    /*for(i = 0; i < heap->heapsz; i++)
    {
        start = (mblock_t*)((u8*)heap->heap+(i<<21));
        if(!(start->size & MBLOCK_ATTR_ALLOC_2MB)) break;
    }
    if(i == heap->heapsz) return NULL;*/
    start = (mblock_t*)heap->data;
    
    //Find free block
    prev = NULL;
    block = start;
    do {
        if((!IS_MBLOCK_ALLOC(block) && mblock_get_size(block) >= size)
            || block->size == 0)
            break;
        prev = block;
        if(block->next) block = block->next;
        else break;
    } while(block);
    if(prev == block) prev = NULL;
    //Allocate
    if(block->size == 0) //Unformatted
    {
        block->size = size|MBLOCK_ATTR_ALLOC;
        block->prev = prev;
        block->next = mblock_get_next(block);
    }
    else heap_split(block,size);
    
    if(prev && !prev->next) prev->next = block;
    
    return block->data;
}

void heap_free(mheap_t* heap, void* mem)
{
    mblock_t* block = (mblock_t*)((u8*)mem - MBLOCK_SIZE);
    (void)heap;
    
    //Unlink
    block->size &= ~MBLOCK_ATTR_ALLOC;
    //Link free blocks prev and next
    heap_join(block,1);
    heap_join(block,-1);
}
