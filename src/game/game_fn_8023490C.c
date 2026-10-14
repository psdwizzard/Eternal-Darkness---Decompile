#include "src/game/types.h"

typedef struct VorbisBlock VorbisBlock;
typedef struct ResidueLook ResidueLook;
typedef struct Codebook Codebook;

s32 fn_802304DC(Codebook *book, float *a, void *b, s32 n);
s32 fn_80234A04(VorbisBlock *vb, ResidueLook *look, s32 **in, s32 ch,
               s32 (*decodepart)(Codebook *, s32 *, void *, s32));

/* Decode residue 0 for the channels that contain nonzero data. */
s32 fn_8023490C(VorbisBlock *vb, ResidueLook *look, register float **in,
               s32 *nonzero, s32 ch) {
    register s32 offset;
    register float **channel;
    register s32 used = 0;
    s32 i;

    offset = 0;

    /* ASM: or (mr) preserves the channel pointer copy; C emits addi with zero. */
    asm { or channel, in, in }

    for (i = 0; i < ch; i++, nonzero++, channel++) {
        if (*nonzero) {
            register float *samples = *channel;
            used++;
            *(float **)((u8 *)in + offset) = samples;
            /* ASM: addic preserves the byte offset that C folds into a pointer. */
            asm { addic offset, offset, 4 }
        }
    }
    if (used) {
        register s32 active;
        register s32 (*decode)(Codebook *, s32 *, void *, s32);
        /* ASM: lis, addi, and or preserve the callback address construction
         * before the count move; C reorders these and emits addi for the move. */
        asm {
            lis active, fn_802304DC@ha
            addi decode, active, fn_802304DC@l
            or active, used, used
        }
        /* The shared inverse currently declares its sample buffers as s32. */
        return fn_80234A04(vb, look, (s32 **)in, active, decode);
    }
    return 0;
}
