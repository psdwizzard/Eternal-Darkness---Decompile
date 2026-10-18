#include "src/game/types.h"

typedef struct EncodeAuxNearestMatch {
    s32 *ptr0;
    s32 *ptr1;
    s32 *p;
    s32 *q;
    s32 aux;
    s32 alloc;
} EncodeAuxNearestMatch;

typedef struct EncodeAuxThreshMatch {
    float *quantthresh;
    s32 *quantmap;
    s32 quantvals;
    s32 threshvals;
} EncodeAuxThreshMatch;

typedef struct StaticCodebook {
    s32 dim;
    s32 entries;
    s32 *lengthlist;
    s32 maptype;
    s32 q_min;
    s32 q_delta;
    s32 q_quant;
    s32 q_sequencep;
    s32 *quantlist;
    EncodeAuxNearestMatch *nearest_tree;
    EncodeAuxThreshMatch *thresh_tree;
    void *pigeon_tree;
    s32 allocedp;
} StaticCodebook;

extern void *memset(void *dest, int value, unsigned long size);

/* vorbis_staticbook_destroy */
void vorbis_staticbook_destroy(void *arg)
{
    register StaticCodebook *book = arg;
    EncodeAuxThreshMatch *thresh;

    if (book->allocedp) {
        if (book->allocedp) {
            if (book->nearest_tree) {
                memset(book->nearest_tree, 0, sizeof(*book->nearest_tree));
            }
            thresh = book->thresh_tree;
            if (thresh) {
                memset(thresh, 0, sizeof(*thresh));
            }
            {
                register StaticCodebook *clear;
                /* ASM: or (mr) preserves the retail register copy for memset;
                 * the C pointer assignment compiles to addi with zero. */
                asm { or clear, book, book }
                memset(clear, 0, sizeof(*clear));
            }
        }
    }
}
