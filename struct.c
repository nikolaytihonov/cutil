#include "struct.h"
#include "cutil.h"

uint struct_size(struct cu_struct_s* st, uint idx, uint8_t* in)
{
    struct cu_value_s* value = &st->members[idx];
    switch (value->type)
    {
    case NoValue: return 0;
    case Sequence: return value->sequence.size;
    //case Array:
    case Int8: return VALUE_INT8_SIZE;
    case Int16: return VALUE_INT16_SIZE;
    case Int32: return VALUE_INT32_SIZE;
    case Int64: return VALUE_INT64_SIZE;
    default: return 0;
    }
}

uint struct_offset(struct cu_struct_s* st, uint idx, uint8_t* in)
{
    uint offset = 0;
    do {
        offset += struct_size(st, idx, in);
    } while (idx--);
    return offset;
}

uint struct_value(struct cu_struct_s* st, uint idx, uint8_t* in, uint8_t* out)
{
    
}
