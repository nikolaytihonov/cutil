#include "struct.h"

struct cu_value_s test_struct[] = {
    {.type = Sequence, .sequence = {.size = 6}},
    {.type = Array, .array = {.item = 4, .count = 12, .index = 0}},
    {.type = Int16},
    {.type = Array, .array = {.item = 14, .count = 3, .index = 1}},
    {.type = NoValue}
};

/*CU_STRUCT_BEGIN(test)
CU_VALUE_SEQUENCE(6)
CU_VALUE_ARRAY(4, 12)
CU_VALUE_INT16()
CU_VALUE_ARRAY_INDEX(14, 3)
CU_STRUCT_END()*/
