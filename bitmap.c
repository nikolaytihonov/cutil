#include "bitmap.h"

uint bit_log2(uint64_t value)
{
    uint pow2 = 0;
    while (value>>=1) pow2++;
    return pow2;
}
