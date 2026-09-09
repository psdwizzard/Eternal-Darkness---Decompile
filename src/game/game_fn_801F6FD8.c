#include "game_state_8063C6B8.h"

typedef struct Int3 {
    unsigned long x;
    unsigned long y;
    unsigned long z;
} Int3;

void fn_801F6FD8(const Int3* value)
{
    *(Int3*)&lbl_8063C6B8[3] = *value;
}
