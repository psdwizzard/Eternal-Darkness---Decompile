#include "src/game/types.h"

/* Vorbis vorbis_book_decodevs_add (interleaved-step vector decode, accumulate). */

typedef struct Codebook {
    s32 dim;
    u8 pad[0x8];
    float *valuelist;
} Codebook;

void *fn_8022F8C4(s32 size);
s32 vorbis_book_decode(Codebook *book, void *b);

s32 vorbis_book_decodevs_add(Codebook *book, float *a, void *b, s32 n) {
    s32 step = n / book->dim;
    s32 *entry = (s32 *)fn_8022F8C4(sizeof(*entry) * step);
    float **t = (float **)fn_8022F8C4(sizeof(*t) * step);
    s32 i, j, o;

    for (i = 0; i < step; i++) {
        entry[i] = vorbis_book_decode(book, b);
        if (entry[i] == -1) {
            return -1;
        }
        t[i] = book->valuelist + entry[i] * book->dim;
    }
    for (i = 0, o = 0; i < book->dim; i++, o += step) {
        for (j = 0; j < step; j++) {
            a[o + j] += t[j][i];
        }
    }
    return 0;
}
