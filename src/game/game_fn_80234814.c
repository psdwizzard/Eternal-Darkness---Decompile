#include "src/game/types.h"

/* Compact the active channels before decoding their residue. */
typedef struct VorbisBlock VorbisBlock;
typedef struct ResidueLook ResidueLook;
typedef struct Codebook Codebook;
typedef s32 (*ResidueDecode)(Codebook *, s32 *, void *, s32);

s32 vorbis_book_decodev_add(Codebook *book, float *samples, void *bits, s32 count);
s32 _01inverse(VorbisBlock *vb, ResidueLook *look, s32 **in, s32 channels,
               ResidueDecode decodepart);

s32 res1_inverse(VorbisBlock *vb, ResidueLook *look, register s32 **in,
               register s32 *nonzero, register s32 channels) {
    register s32 **source;
    register s32 used = 0;

    /* ASM: mr preserves the retail register copy; C emits addi instead. */
    asm { mr source, in }
    /* ASM: li/mtctr keep the byte offset in r8 and set the loop count
     * before the guard; C schedules the comparison first. */
    asm {
        li r8, 0
        mtctr channels
    }

    if (channels > 0) {
    channel_loop:
        if (*nonzero) {
            register s32 *value = *source;
            used++;
            /* ASM: stwx/addi preserve the indexed output cursor that C
             * strength reduction replaces with a separate pointer. */
            asm {
                stwx value, in, r8
                addi r8, r8, 4
            }
        }
        nonzero++;
        source++;
        /* ASM: bdnz uses the count initialized above; a C loop adds
         * another mtctr after the guard comparison. */
        asm { bdnz channel_loop }
    }
    if (used) {
        register s32 count;
        register ResidueDecode decodepart;
        /* ASM: lis/addi/mr set the decoder and active-channel count.
         * C selects addi for the count copy instead of the retail mr. */
        asm {
            lis r6, vorbis_book_decodev_add@ha
            addi decodepart, r6, vorbis_book_decodev_add@l
            mr count, used
        }
        return _01inverse(vb, look, in, count, decodepart);
    }
    return 0;
}

