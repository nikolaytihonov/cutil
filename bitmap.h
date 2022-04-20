#ifndef __BITMAP_H
#define __BITMAP_H

#include "cutypes.h"

#define bit_set(v, p, b) (v)=(b?(v)|(1<<(p)):(v)^(1<<(p)))
#define bit_get(v, p) ((v>>(p))&1)
#define bit_test(v, p) (!!(v&(1<<(p))))
#define bit_sub2_up(v, p) ((v>>(p))+!!(v&((1<<(p))-1)))
#define bit_align2(v, p) (bit_sub2_up(v, (p))<<(p))
uint bit_log2(uint64_t value);

#define bitmap(name, s) uword name[bit_sub2_up(s, CU_WORD_POW2)] = {0}
#define bitmap_set(m, p, b) \
    bit_set((m)[p>>CU_WORD_POW2], p&((1<<CU_WORD_POW2)-1), b)
#define bitmap_get(m, p)    \
    bit_get((m)[p>>CU_WORD_POW2], p&((1<<CU_WORD_POW2)-1))

#endif