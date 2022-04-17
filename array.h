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

#define array_at(array, i) ((uint8_t*)(array)->mem + (i)*(array)->size)
#define array_first(array) array_at(array, 0)
#define array_last(array) array_at(array, (array)->count - 1)

void array_push(array_t* array, const void* data);
void array_pop(array_t* array, void* src);

#endif