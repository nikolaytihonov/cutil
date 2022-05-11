#include "bitmap.h"

uint bit_log2(u64 value)
{
    uint pow2 = 0;
    while (value>>=1) pow2++;
    return pow2;
}
