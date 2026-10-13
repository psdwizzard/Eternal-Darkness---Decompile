#include "src/game/types.h"

/* Vorbis codebook and its packed-entry decoding table. */
typedef struct DecodeAux {
    s16 *tab;
    s16 *tabl;
    s16 tabn;
    s16 *ptr0;
    s16 *ptr1;
} DecodeAux;

typedef struct Codebook {
    s32 dim;
    s32 entries;
    void *c;
    void *valuelist;
    void *quantlist;
    DecodeAux *decode_tree;
} Codebook;

typedef struct OggPackBuffer OggPackBuffer;
extern s32 fn_80230718(Codebook *book, OggPackBuffer *b);

/* Decode successive codebook vectors into the output buffer. */
s32 fn_80230204(register Codebook *book, register float *a,
                register OggPackBuffer *b, register s32 n)
{
    register s32 outputOffset;
    register s32 i;
    register s32 valueOffset;
    register s32 j;
    s32 entry;
    register const float *values;

    /* ASM: or (mr) preserves argument moves; C emits addi with zero. */
    asm {
        or book, book, book
        or a, a, a
        or b, b, b
        or n, n, n
    }
    for (i = 0, outputOffset = 0; i < n;) {
        register Codebook *callBook;
        register OggPackBuffer *callBuffer;

        /* ASM: or (mr) emits the call argument moves instead of addi with zero. */
        asm {
            or callBook, book, book
            or callBuffer, b, b
        }
        entry = fn_80230718(callBook, callBuffer);
        if (entry == -1) {
            return -1;
        }
        values = (float *)book->valuelist + entry * book->dim;
        for (j = 0, valueOffset = 0; j < book->dim;) {
            register float value;
            value = *(const float *)((const u8 *)values + valueOffset);
            j++;
            /* ASM: addic preserves a byte cursor that C folds into a pointer. */
            asm { addic valueOffset, valueOffset, 4 }
            /* ASM: addi and stfsx preserve the counter update before the store;
             * C schedules this independent increment after the store. */
            asm {
                addi i, i, 1
                stfsx value, a, outputOffset
            }
            /* ASM: addic preserves the independent output byte cursor. */
            asm { addic outputOffset, outputOffset, 4 }
        }
    }
    return 0;
}
