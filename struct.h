#ifndef __STRUCT_H
#define __STRUCT_H

#include "cutypes.h"

enum cu_value_type_e {
    NoValue,
    Sequence,
    Array,
    Int8,
    Int16,
    Int32,
    Int64
};

struct cu_value_s {
    enum cu_value_type_e type;
    union {
        struct {
            uint size;
        } sequence;
        struct {
            uint item;
            uint count : 31;
            uint index : 1;
        } array;
    };
};

#define CU_STRUCT_BEGIN(name)   \
    struct cu_value_s cu_struct_##name[] = {
#define CU_STRUCT_END() \
    {.type = NoValue}};
#define CU_VALUE_INT8()     {.type = Int8},
#define CU_VALUE_INT16()    {.type = Int16}, 
#define CU_VALUE_INT32()    {.type = Int32},
#define CU_VALUE_INT64()    {.type = Int64},
#define CU_VALUE_SEQUENCE(_size) \
    {.type = Sequence, .sequence = {.size = (_size)}},
#define CU_VALUE_ARRAY(_item, _count) \
    {.type = Array, .array = {.item = (_item), .count = (_count), .index = 0}},
#define CU_VALUE_ARRAY_INDEX(_item, _index) \
    {.type = Array, .array = {.item = (_item), .count = (_index), .index = 1}},

typedef void (*cu_value_operate)(struct cu_value_s* type,
    uint8_t** in, uint8_t** out);

#endif