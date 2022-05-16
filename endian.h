#ifndef __CUTIL_ENDIAN_H
#define __CUTIL_ENDIAN_H

#include "cutypes.h"

enum cu_endian_e {
    LittleEndian,
    BigEndian
};

extern enum cu_endian_e cu_endian;

typedef u16 (*bswap16_t)(u16);
typedef u32 (*bswap32_t)(u32);
typedef u64 (*bswap64_t)(u64);

extern bswap16_t cu_bswap16;
extern bswap32_t cu_bswap32;
extern bswap64_t cu_bswap64;

extern bswap16_t h16tol16;
extern bswap32_t h32tol32;
extern bswap64_t h64tol64;
extern bswap16_t l16toh16;
extern bswap32_t l32toh32;
extern bswap64_t l64toh64;

extern bswap16_t h16tob16;
extern bswap32_t h32tob32;
extern bswap64_t h64tob64;
extern bswap16_t b16toh16;
extern bswap32_t b32toh32;
extern bswap64_t b64toh64;

#define CU_NETWORK_ORDER BigEndian

extern bswap16_t h16ton16;
extern bswap32_t h32ton32;
extern bswap64_t h64ton64;
extern bswap16_t n16toh16;
extern bswap32_t n32toh32;
extern bswap64_t n64toh64;

void cu_endian_init();

#endif