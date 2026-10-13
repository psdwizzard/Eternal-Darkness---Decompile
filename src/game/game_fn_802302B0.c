#include "src/game/types.h"

/* Vorbis vector codebook decode and accumulation. */
typedef struct Codebook {
    s32 dim;
    u8 pad[0x8];
    float *valuelist;
} Codebook;

s32 fn_80230718(Codebook *book, void *b);

s32 fn_802302B0(Codebook *book, float *a, void *b, s32 n) {
    s32 i, j, entry;
    float *t;
    s32 offset;

    if (book->dim > 8) {
        for (i = 0, offset = 0; i < n;) {
            entry = fn_80230718(book, b);
            if (entry == -1) {
                return -1;
            }
            t = book->valuelist + entry * book->dim;
            for (j = 0; j < book->dim;) {
                float value = t[j++];
                /* Advance the byte cursor while accumulating into its old slot. */
                *(float *)((u8 *)a + (offset += sizeof(float)) - sizeof(float)) += value;
                i++;
            }
        }
    } else {
        for (i = 0; i < n;) {
            entry = fn_80230718(book, b);
            if (entry == -1) {
                return -1;
            }
            t = book->valuelist + entry * book->dim;
            j = 0;
            /* Each case consumes one component, then falls through. */
            switch (book->dim) {
            case 8:
                a[i++] += t[j];
                j++;
            case 7:
                a[i] += t[j];
                j++;
                i++;
            case 6:
                a[i] += t[j++];
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
