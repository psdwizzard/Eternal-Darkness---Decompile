#include "src/game/types.h"

/* libogg oggpack_readinit: initialize a bit-packing buffer for reading. */
typedef struct oggpack_buffer {
    s32 endbyte;
    s32 endbit;
    u8 *buffer;
    u8 *ptr;
    s32 storage;
} oggpack_buffer;

extern void *memset(void *dest, int value, unsigned long size);

void fn_8022EA4C(oggpack_buffer *b, u8 *buffer, s32 bytes) {
    b = memset(b, 0, sizeof(*b));
    b->buffer = b->ptr = buffer;
    b->storage = bytes;
}
