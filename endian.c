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
    return  (val & 0xFF000000U) >> 24
        |   (val & 0x00FF0000U) >> 8
        |   (val & 0x0000FF00U) << 8
        |   (val & 0x000000FFU) << 24;
}

static uint64_t sw_bswap64(uint64_t val)
{
    return  (val & 0xFF00000000000000UL) >> 56
        |   (val & 0x00FF000000000000UL) >> 40
        |   (val & 0x0000FF0000000000UL) >> 24
        |   (val & 0x000000FF00000000UL) >> 8
        |   (val & 0x00000000FF000000UL) << 8
        |   (val & 0x0000000000FF0000UL) << 24
        |   (val & 0x000000000000FF00UL) << 40
        |   (val & 0x00000000000000FFUL) << 56;
}

#include <stdio.h>

void cu_endian_init()
{
    cu_endian = endian_detect();
    printf("%x\t%x\n", 0x12345678, sw_bswap32(0x12345678));
    printf("%lx\t%lx\n", 0x12345678abcd8765, sw_bswap64(0x12345678abcd8765));
}
