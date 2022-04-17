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
void array_clear(array_t* array);

#define array_at(array, i) ((uint8_t*)(array)->mem + (i)*(array)->size)
#define array_first(array) array_at(array, 0)
#define array_last(array) array_at(array, (array)->count - 1)

uint array_align(array_t* array, uint count);
void array_resize(array_t* array, uint newCount);

#define CU_ARRAY_FOREACH(array) \
    for (uint i = 0; i < (array)->count; i++)

void array_push(array_t* array, const void* data);
void array_pop(array_t* array, void* src);

#endif