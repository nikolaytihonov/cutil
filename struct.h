#ifndef __STRUCT_H
#define __STRUCT_H

#include "cutypes.h"
#include "endian.h"

#define VALUE_INT8_SIZE     sizeof(u8)
#define VALUE_INT16_SIZE    sizeof(u16)
#define VALUE_INT32_SIZE    sizeof(u32)
#define VALUE_INT64_SIZE    sizeof(u64)

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
            uint count  :   31;
            uint index  :   1;
        } array;
    };
};

struct cu_struct_s {
    enum cu_endian_e endian;
    struct cu_value_s members[];
};

#define CU_STRUCT(name) &cu_struct_##name
#define CU_STRUCT_BEGIN(_name, _endian)     \
    struct cu_struct_s cu_struct_##_name =  \
    {.endian = _endian, .members = {
#define CU_STRUCT_END() \
    {.type = NoValue}}};
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
#define CU_VALUE_ARRAY_ZERO(_item)  \
    {.type = Array, .array = {.item = (_item), .count = 0, .index = 0}},

uint value_size(struct cu_struct_s* st, uint idx, const void* in);
uint value_offset(struct cu_struct_s* st, uint idx, const void* in);
void value_get(struct cu_struct_s* st, uint idx, const void* in, void* out);
uint value_array_size(struct cu_struct_s* st, uint idx, const void* in);

uint struct_size(struct cu_struct_s* st, const void* in);

#endif