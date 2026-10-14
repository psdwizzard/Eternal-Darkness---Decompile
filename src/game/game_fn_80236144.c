#include "src/game/types.h"

/* Return the number of bits needed to represent value. */
s32 fn_80236144(u32 value) {
    s32 bits = 0;

    while (value != 0) {
        value >>= 1;
        bits++;
    }

    return bits;
}
