#include "src/game/types.h"

extern void *memset(void *, int, unsigned long);

typedef struct VorbisDspState VorbisDspState;

typedef struct VorbisBlock {
    u8 pad00[0x38];
    VorbisDspState *state;
    void *localStore;
    s32 localTop;
    s32 localAlloc;
    u8 pad48[0x1C];
} VorbisBlock;

s32 fn_802300D0(register VorbisDspState *state, register VorbisBlock *block)
{
    register VorbisBlock *destination;

    /* ASM: or (mr) passes the block pointer; C emits addi with zero. */
    asm { or destination, block, block }
    memset(destination, 0, sizeof(*block));
    block->state = state;
    block->localAlloc = 0;
    block->localStore = 0;
    return 0;
}
