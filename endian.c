#include "endian.h"

enum cu_endian_e cu_endian;

static const union {
    uint8_t bytes[4];
    uint32_t value;
} host_order = {
    {0, 1, 2, 3}
};

#define ORDER_LITTLE_ENDIAN     0x03020100
#define ORDER_BIG_ENDIAN        0x00010203

static enum cu_endian_e endian_detect()
{
    if (host_order.value == ORDER_LITTLE_ENDIAN)
        return LittleEndian;
    else if (host_order.value == ORDER_BIG_ENDIAN)
        return BigEndian;
    else return MiddleEndian;
}

static uint16_t sw_bswap16(uint16_t val)
{
    return (val << 8) | (val >> 8);
}

static uint32_t sw_bswap32(uint32_t val)
{
    return  ((val >> 24) & 0xFF) << 0
        |   ((val >> 16) & 0xFF) << 8
        |   ((val >> 8) & 0xFF) << 16
        |   ((val >> 0) & 0xFF) << 24;
}

static uint64_t sw_bswap64(uint64_t val)
{
    return  ((val >> 56) & 0xFF) << 0
        |   ((val >> 48) & 0xFF) << 8
        |   ((val >> 40) & 0xFF) << 16
        |   ((val >> 32) & 0xFF) << 24
        |   ((val >> 24) & 0xFF) << 32
        |   ((val >> 16) & 0xFF) << 40
        |   ((val >> 8) & 0xFF) << 48
        |   ((val >> 0) & 0xFF) << 56;
}

#include <stdio.h>

void cu_endian_init()
{
    cu_endian = endian_detect();
    printf("%lx\t%lx\n", 0x12345678abcd8765, sw_bswap64(0x12345678abcd8765));
}
