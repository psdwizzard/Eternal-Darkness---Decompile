#include "src/game/types.h"

/* Vorbis vorbis_book_decodevv_add: interleaved multi-channel accumulate. */
typedef struct Codebook {
    s32 dim;
    u8 pad[0x8];
    float *valuelist;
} Codebook;

s32 fn_80230718(Codebook *book, void *b);

s32 fn_80230128(Codebook *book, float **a, s32 offset, s32 ch, void *b, s32 n) {
    s32 chptr = 0;
    s32 i, j, entry;

    for (i = offset / ch; i < (offset + n) / ch;) {
        entry = fn_80230718(book, b);
        if (entry == -1) {
            return -1;
        }
        {
            const float *t = book->valuelist + entry * book->dim;
            for (j = 0; j < book->dim; j++) {
                a[chptr++][i] += t[j];
                if (chptr == ch) {
                    chptr = 0;
                    i++;
                }
            }
        }
    }
    return 0;
}
