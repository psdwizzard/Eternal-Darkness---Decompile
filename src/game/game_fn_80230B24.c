/* Vorbis floor0 inverse2: apply the decoded floor, or silence the curve. */

#include "src/game/types.h"

typedef struct Floor0Info {
    u8 pad00[0x10];
    s32 ampdB;
} Floor0Info;

typedef struct Floor0Look {
    s32 n;
    s32 ln;
    s32 m;
    s32 *linearmap;
    Floor0Info *vi;
} Floor0Look;

typedef struct VorbisBlock VorbisBlock;

extern void vorbis_lsp_to_curve(float *curve, int *map, int count, int bins,
                       float *lsp, int order, float amplitude, float offset);
extern void *memset(void *dest, int value, unsigned long size);

s32 floor0_inverse2(VorbisBlock *vb, volatile Floor0Look *look, void *memo, float *out) {
    Floor0Info *info = look->vi;

    if (memo != 0) {
        float *lsp = memo;
        vorbis_lsp_to_curve(out, look->linearmap, look->n, look->ln,
                    lsp, look->m, ((float *)memo)[look->m], (float)info->ampdB);
        return 1;
    }

    memset(out, 0, look->n * sizeof(*out));
    return 0;
}

