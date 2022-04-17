#ifndef __ARRAY_H
#define __ARRAY_H

#include "cutypes.h"

typedef struct {
    void* mem;
    uint size;
    uint count;
    uint align;
} array_t;

void array_init(array_t* array, uint size, uint align);
void array_alloc(array_t* array, uint newCount);
void array_clear(array_t* array);

void array_push(array_t* array, const void* data);

#endif