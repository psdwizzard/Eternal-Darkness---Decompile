#include "src/game/types.h"

/* libogg oggpack_adv: advance the bit-packing buffer by the given bit count. */
typedef struct oggpack_buffer {
    s32 endbyte;
    s32 endbit;
    u8 *buffer;
    u8 *ptr;
    s32 storage;
} oggpack_buffer;

void oggpack_adv(oggpack_buffer *b, register s32 bits) {
    register s32 bytes;
    register s32 shifted;
    bits += b->endbit;
    /* ASM: srawi and addze implement signed division by eight; C's division
     * expression changes the retail register allocation and scheduling. */
    asm {
        srawi shifted, bits, 3
        addze bytes, shifted
    }
    b->ptr += bytes;
    b->endbyte += bytes;
    b->endbit = bits & 7;
}
