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

#if (CU_ARCH == x86_32)
static uint32_t hw_bswap32(uint32_t val)
{
    __asm__ ("bswap %0" : "=r" (val) : "r" (val));
    return val;
}

bswap16_t cu_bswap16 = sw_bswap16;
bswap32_t cu_bswap32 = hw_bswap32;
bswap64_t cu_bswap64 = sw_bswap64;
#elif (CU_ARCH == x86_64)
static uint32_t hw_bswap32(uint32_t val)
{
    __asm__ ("bswap %0" : "=r" (val) : "r" (val));
    return val;
}

static uint64_t hw_bswap64(uint64_t val)
{
    __asm__ ("bswap %0" : "=r" (val) : "r" (val));
    return val;
}

bswap16_t cu_bswap16 = sw_bswap16;
bswap32_t cu_bswap32 = hw_bswap32;
bswap64_t cu_bswap64 = hw_bswap64;
#else
bswap16_t cu_bswap16 = sw_bswap16;
bswap32_t cu_bswap32 = sw_bswap32;
bswap64_t cu_bswap64 = sw_bswap64;
#endif

void cu_endian_init()
{
    cu_endian = endian_detect();
}
