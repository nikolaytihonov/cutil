#ifndef __ARRAY_H
#define __ARRAY_H

#include "cutypes.h"

typedef struct {
    uint size;
    uint count;
    uint align;
    uint8_t data[1];
} array_t;

#define CU_ARRAY_HEAD_SIZE (sizeof(uint) * 3)

array_t* array_create(uint size, uint align, uint reserve);
void array_delete(array_t* array);

void* array_push(array_t* array, const void* data);

#endif