#ifndef __BITMAP_H
#define __BITMAP_H

#include "cutypes.h"

#define bit_align2(v, p) (((v>>p)+!!(v&((1<<p)-1)))<<p)
uint bit_log2(uint64_t value);

#endif