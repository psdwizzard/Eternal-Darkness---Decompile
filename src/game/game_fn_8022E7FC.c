#include "src/game/types.h"

/* libogg oggpack_read1: read one bit and advance the bit-packing buffer. */
typedef struct oggpack_buffer {
    s32 endbyte;
    s32 endbit;
    u8 *buffer;
    u8 *ptr;
    s32 storage;
} oggpack_buffer;

s32 oggpack_read1(oggpack_buffer *b) {
    s32 ret;

    if (b->endbyte >= b->storage) {
        ret = -1;
    } else {
        ret = (b->ptr[0] >> b->endbit) & 1;
    }

    b->endbit++;
    if (b->endbit > 7) {
        b->endbit = 0;
        b->ptr++;
        b->endbyte++;
    }
    return ret;
}
