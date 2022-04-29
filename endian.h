#ifndef __ENDIAN_H
#define __ENDIAN_H

#include "cutypes.h"

enum cu_endian_e {
    LittleEndian,
    BigEndian,
    MiddleEndian
};

extern enum cu_endian_e cu_endian;

typedef uint16_t (*bswap16_t)(uint16_t);
typedef uint32_t (*bswap32_t)(uint32_t);
typedef uint64_t (*bswap64_t)(uint64_t);

extern bswap16_t cu_bswap16;
extern bswap32_t cu_bswap32;
extern bswap64_t cu_bswap64;

void cu_endian_init();

#endif