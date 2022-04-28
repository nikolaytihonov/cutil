#ifndef __ENDIAN_H
#define __ENDIAN_H

#include "cutypes.h"

enum cu_endian_e {
    LittleEndian,
    BigEndian,
    PDPEndian,
    HoneywellEndian
};

extern enum cu_endian_e cu_endian;

void cu_endian_init();

#endif