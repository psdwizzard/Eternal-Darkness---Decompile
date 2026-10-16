#include "src/game/types.h"

/* Vorbis vector codebook decode and accumulation. */
typedef struct DecodeAux DecodeAux;
typedef struct OggPackBuffer OggPackBuffer;

typedef struct Codebook {
    s32 dim;
    s32 entries;
    void *c;
    void *valuelist;
    void *quantlist;
    DecodeAux *decode_tree;
} Codebook;

s32 fn_80230718(Codebook *book, OggPackBuffer *b);

s32 fn_802302B0(register Codebook *book, register float *a, register OggPackBuffer *b, register s32 n) {
    register s32 i, j;
    s32 entry;
    register s32 valueOffset;
    register float *t;
    register s32 offset;

    /* ASM: or emits register copies instead of addi with zero. */
    asm {
        or a, a, a
        or b, b, b
        or n, n, n
    }
    if (book->dim > 8) {
        for (i = 0, offset = 0; i < n;) {
            register Codebook *cb;
            register OggPackBuffer *bb;
            /* ASM: or emits call argument moves instead of addi with zero. */
            asm {
                or cb, book, book
                or bb, b, b
            }
            entry = fn_80230718(cb, bb);
            if (entry == -1) {
                return -1;
            }
            t = (float *)book->valuelist + entry * book->dim;
            for (j = 0, valueOffset = 0; j < book->dim;) {
                register float value, accumulated;
                value = *(float *)((u8 *)t + valueOffset);
                i++;
                accumulated = *(float *)((u8 *)a + offset);
                accumulated += value;
                *(float *)((u8 *)a + offset) = accumulated;
                j++;

                /* ASM: addic keeps the byte cursor that C folds into a pointer. */
                asm { addic valueOffset, valueOffset, 4 }
                /* ASM: addic retains independent byte cursors that C folds into pointers. */
                asm { addic offset, offset, 4 }
            }
        }
    } else {
        for (i = 0; i < n;) {
            register Codebook *cb;
            register OggPackBuffer *bb;
            /* ASM: or emits call argument moves instead of addi with zero. */
            asm {
                or cb, book, book
                or bb, b, b
            }
            entry = fn_80230718(cb, bb);
            if (entry == -1) {
                return -1;
            }
            t = (float *)book->valuelist + entry * book->dim;
            j = 0;
            /* Each case consumes one component, then falls through. */
            switch (book->dim) {
            case 8:
                a[i] += t[j];
                i++;
                j++;
            case 7:
                a[i] += t[j];
                j++;
                i++;
            case 6:
                a[i] += t[j];
                j++;
                i++;
            case 5:
                a[i] += t[j];
                i++;
                j++;
            case 4:
                a[i] += t[j];
                i++;
                j++;
            case 3:
                a[i] += t[j];
                i++;
                j++;
            case 2:
                a[i] += t[j];
                i++;
                j++;
            case 1:
                a[i] += t[j];
                i++;
                j++;
            case 0:
                break;
            }
        }
    }
    return 0;
}
