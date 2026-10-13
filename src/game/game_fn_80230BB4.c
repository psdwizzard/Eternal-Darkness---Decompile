/* fn_80230BB4: Vorbis floor0 inverse1 (floor0_inverse1). */

#include "src/game/types.h"

typedef struct Floor0Info {
    u8 pad00[0x0C];
    s32 ampbits;   /* 0x0C */
    s32 ampdB;     /* 0x10 */
    s32 numbooks;  /* 0x14 */
    s32 books[16]; /* 0x18 */
} Floor0Info;

typedef struct Floor0Look {
    u8 pad00[0x08];
    s32 m;          /* 0x08 */
    u8 pad0C[0x04];
    Floor0Info *vi; /* 0x10 */
} Floor0Look;

typedef struct Codebook {
    s32 dim; /* 0x00 */
    u8 pad04[0x1C - 0x04];
} Codebook;

typedef struct CodecSetup {
    u8 pad00[0x0C];
    Codebook *fullbooks; /* 0x0C */
} CodecSetup;

typedef struct VorbisDsp {
    u8 pad00[0x48];
    CodecSetup *codec_setup; /* 0x48 */
} VorbisDsp;

typedef struct VorbisBlock {
    u8 pad00[0x04];
    u8 opb[0x38 - 0x04]; /* 0x04 */
    VorbisDsp *vd;       /* 0x38 */
} VorbisBlock;

extern s32 fn_8022E868(void *, s32);
extern void *fn_8022F8C4(s32 size);
extern s32 fn_80230204(Codebook *book, float *vec, void *opb, s32 n);
extern s32 fn_80236144(u32);
extern const float lbl_806517B8; /* 0.0f */

float *fn_80230BB4(VorbisBlock *vb, Floor0Look *look) {
    Floor0Info *info = look->vi;
    s32 j, k;

    s32 ampraw = fn_8022E868(vb->opb, info->ampbits);
    if (ampraw > 0) {
        s32 maxval = (1 << info->ampbits) - 1;
        float amp = (float)ampraw / maxval * info->ampdB;
        s32 booknum = fn_8022E868(vb->opb, fn_80236144(info->numbooks));

        if (booknum != -1 && booknum < info->numbooks) {
            CodecSetup *ci = vb->vd->codec_setup;
            Codebook *b = ci->fullbooks + info->books[booknum];
            float last = lbl_806517B8;
            float *lsp = fn_8022F8C4(sizeof(*lsp) * (look->m + 1));

            for (j = 0; j < look->m; j += b->dim)
                if (fn_80230204(b, lsp + j, vb->opb, b->dim) == -1) goto eop;
            for (j = 0; j < look->m;) {
                for (k = 0; k < b->dim; k++, j++) lsp[j] += last;
                last = lsp[j - 1];
            }

            lsp[look->m] = amp;
            return lsp;
        }
    }
eop:
    return 0;
}
