#include "src/game/types.h"

/* Vorbis static_codebook (codebook.h) */
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
} StaticCodebook;

extern void *fn_8022F780(s32 size);           /* _ogg_malloc */
extern double fn_80101C30(double value, int n); /* ldexp */
extern s32 fn_80235B10(StaticCodebook *b);     /* _book_maptype1_quantvals */

#define VQ_FMAN 21
#define VQ_FEXP_BIAS 768

static float _float32_unpack(s32 val)
{
    double mant = val & 0x1fffff;
    s32 sign = val & 0x80000000;
    s32 exp = (val & 0x7fe00000) >> VQ_FMAN;
    if (sign) {
        mant = -mant;
    }
    return fn_80101C30(mant, exp - (VQ_FMAN - 1) - VQ_FEXP_BIAS);
}

/* _book_unquantize */
float *fn_802358A0(StaticCodebook *b)
{
    s32 j, k;

    if (b->maptype == 1 || b->maptype == 2) {
        s32 quantvals;
        float mindel = _float32_unpack(b->q_min);
        float delta = _float32_unpack(b->q_delta);
        float *r = fn_8022F780(b->entries * b->dim * sizeof(*r));

        switch (b->maptype) {
        case 1:
            quantvals = fn_80235B10(b);
            for (j = 0; j < b->entries; j++) {
                float last = 0.0f;
                s32 indexdiv = 1;
                for (k = 0; k < b->dim; k++) {
                    s32 index = (j / indexdiv) % quantvals;
                    float val = b->quantlist[index];
                    val = (float)__fabs(val) * delta + mindel + last;
                    if (b->q_sequencep) {
                        last = val;
                    }
                    r[j * b->dim + k] = val;
                    indexdiv *= quantvals;
                }
            }
            break;
        case 2:
            for (j = 0; j < b->entries; j++) {
                float last = 0.0f;
                for (k = 0; k < b->dim; k++) {
                    float val = b->quantlist[j * b->dim + k];
                    val = (float)__fabs(val) * delta + mindel + last;
                    if (b->q_sequencep) {
                        last = val;
                    }
                    r[j * b->dim + k] = val;
                }
            }
            break;
        }
        return r;
    }
    return 0;
}
