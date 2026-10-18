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

void oggpack_readinit(register oggpack_buffer *b, register u8 *buffer, register s32 bytes) {
    register s32 saved_bytes;
    register u8 *saved_buffer;
    register unsigned long length;
    register int zero;
    /* ASM: or (mr) and li retain the register-copy encodings and argument
     * setup order; C uses addi copies and moves the immediate loads. */
    asm {
        or saved_bytes, bytes, bytes
        li length, 20
        or saved_buffer, buffer, buffer
        li zero, 0
    }
    b = memset(b, zero, length);
    b->buffer = b->ptr = saved_buffer;
    b->storage = saved_bytes;
}
