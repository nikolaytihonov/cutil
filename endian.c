#include "endian.h"

enum cu_endian_e cu_endian;

static const union {
    u8 bytes[4];
    u32 value;
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
}

static u16 sw_bswap16(u16 val)
{
    return (val << 8) | (val >> 8);
}

static u32 sw_bswap32(u32 val)
{
    return  (val & 0xFF000000U) >> 24
        |   (val & 0x00FF0000U) >> 8
        |   (val & 0x0000FF00U) << 8
        |   (val & 0x000000FFU) << 24;
}

static u64 sw_bswap64(u64 val)
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
extern u16 hw_bswap16(u16 val);
extern u32 hw_bswap32(u32 val);

bswap16_t cu_bswap16 = hw_bswap16;
bswap32_t cu_bswap32 = hw_bswap32;
bswap64_t cu_bswap64 = sw_bswap64;
#elif (CU_ARCH == x86_64)
extern u16 hw_bswap16(u16 val);
extern u32 hw_bswap32(u32 val);
extern u64 hw_bswap64(u64 val);

bswap16_t cu_bswap16 = hw_bswap16;
bswap32_t cu_bswap32 = hw_bswap32;
bswap64_t cu_bswap64 = hw_bswap64;
#elif (CU_ARCH == AARCH64)
extern u16 hw_bswap16(u16 val);
extern u32 hw_bswap32(u32 val);
extern u64 hw_bswap64(u64 val);

bswap16_t cu_bswap16 = hw_bswap16;
bswap32_t cu_bswap32 = hw_bswap32;
bswap64_t cu_bswap64 = hw_bswap64;
#else
bswap16_t cu_bswap16 = sw_bswap16;
bswap32_t cu_bswap32 = sw_bswap32;
bswap64_t cu_bswap64 = sw_bswap64;
#endif

static u16 no_bswap16(u16 val)
{
    return val;
}

static u32 no_bswap32(u32 val)
{
    return val;
}

static u64 no_bswap64(u64 val)
{
    return val;
}

bswap16_t h16tol16 = no_bswap16;
bswap32_t h32tol32 = no_bswap32;
bswap64_t h64tol64 = no_bswap64;
bswap16_t l16toh16 = no_bswap16;
bswap32_t l32toh32 = no_bswap32;
bswap64_t l64toh64 = no_bswap64;

bswap16_t h16tob16 = no_bswap16;
bswap32_t h32tob32 = no_bswap32;
bswap64_t h64tob64 = no_bswap64;
bswap16_t b16toh16 = no_bswap16;
bswap32_t b32toh32 = no_bswap32;
bswap64_t b64toh64 = no_bswap64;

bswap16_t h16ton16 = no_bswap16;
bswap32_t h32ton32 = no_bswap32;
bswap64_t h64ton64 = no_bswap64;
bswap16_t n16toh16 = no_bswap16;
bswap32_t n32toh32 = no_bswap32;
bswap64_t n64toh64 = no_bswap64;

void cu_endian_init()
{
    cu_endian = endian_detect();
    if (cu_endian == LittleEndian)
    {
        h16tob16 = cu_bswap16;
        h32tob32 = cu_bswap32;
        h64tob64 = cu_bswap64;
        b16toh16 = cu_bswap16;
        b32toh32 = cu_bswap32;
        b64toh64 = cu_bswap64;
    }
    else if (cu_endian == BigEndian)
    {
        h16tol16 = cu_bswap16;
        h32tol32 = cu_bswap32;
        h64tol64 = cu_bswap64;
        l16toh16 = cu_bswap16;
        l32toh32 = cu_bswap32;
        l64toh64 = cu_bswap64;
    }

    if (cu_endian != CU_NETWORK_ORDER)
    {
        h16ton16 = cu_bswap16;
        h32ton32 = cu_bswap32;
        h64ton64 = cu_bswap64;
        n16toh16 = cu_bswap16;
        n32toh32 = cu_bswap32;
        n64toh64 = cu_bswap64;
    }
}
