#include "src/game/types.h"

/* libogg oggpack_look: peek at up to 32 bits from a bit-packing buffer. */

typedef struct oggpack_buffer {
    s32 endbyte;
    s32 endbit;
    u8 *buffer;
    u8 *ptr;
    s32 storage;
} oggpack_buffer;

extern const u32 lbl_802FF840[33]; /* mask */

s32 fn_8022E988(oggpack_buffer *b, s32 bits) {
    u32 ret;
    u32 m = lbl_802FF840[bits];

    bits += b->endbit;

    if (b->endbyte + 4 >= b->storage) {
        if (b->storage * 8 < bits + b->endbyte * 8) return -1;
    }

    ret = b->ptr[0] >> b->endbit;
    if (bits > 8) {
        ret |= b->ptr[1] << (8 - b->endbit);
        if (bits > 16) {
            ret |= b->ptr[2] << (16 - b->endbit);
            if (bits > 24) {
                ret |= b->ptr[3] << (24 - b->endbit);
                if (bits > 32 && b->endbit) {
                    ret |= b->ptr[4] << (32 - b->endbit);
                }
            }
        }
    }
    return m & ret;
}
