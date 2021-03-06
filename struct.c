#include "struct.h"
#include "cutil.h"

union intvalue_u {
    u8 int8;
    u16 int16;
    u32 int32;
    u64 int64;
};

uint value_size(struct cu_struct_s* st, uint idx, const void* in)
{
    struct cu_value_s* value = &st->members[idx];
    switch (value->type)
    {
    case NoValue: return 0;
    case Sequence: return value->sequence.size;
    case Array: return value_array_size(st, idx, in);
    case Int8: return VALUE_INT8_SIZE;
    case Int16: return VALUE_INT16_SIZE;
    case Int32: return VALUE_INT32_SIZE;
    case Int64: return VALUE_INT64_SIZE;
    default: return 0;
    }
}

uint value_offset(struct cu_struct_s* st, uint idx, const void* in)
{
    uint offset = 0;
    while (idx--) offset += value_size(st, idx, in);
    return offset;
}

void value_get(struct cu_struct_s* st, uint idx, const void* in, void* out)
{
    uint size = value_size(st, idx, in);
    uint offset = value_offset(st, idx, in);
    struct cu_value_s* value = &st->members[idx];
    union intvalue_u* data = (union intvalue_u*)out;

    if (size) cu_memcpy(out, in + offset, size);
    else return;

    if (st->endian != cu_endian)
    {
        switch (value->type)
        {
        case Int8: break;
        case Int16: data->int16 = cu_bswap16(data->int16); break;
        case Int32: data->int32 = cu_bswap32(data->int32); break;
        case Int64: data->int64 = cu_bswap64(data->int64); break;
        }
    }
}

uint value_array_size(struct cu_struct_s* st, uint idx, const void* in)
{
    union intvalue_u count = {0};
    struct cu_value_s* value = &st->members[idx];
    
    if (value->array.index)
    {
        if (value->array.count != idx)
            value_get(st, value->array.count, in, &count);
    }
    else if (value->array.count)
    {
        count.int32 = value->array.count;
    }
    else
    {
        const u8* items = (const u8*)in + value_offset(st, idx, in);
        uint size = value->array.item;
        while (cu_memtest(items, size))
        {
            items += size;
            count.int32++;
        }
    }
    
    return value->array.item * count.int32;
}

uint struct_size(struct cu_struct_s* st, const void* in)
{
    uint idx = 0;
    struct cu_value_s* value = st->members;
    while ((value++)->type != NoValue) idx++;
    return value_offset(st, idx, in);
}
