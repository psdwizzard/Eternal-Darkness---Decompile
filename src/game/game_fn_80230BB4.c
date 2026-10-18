/* floor0_inverse1: Vorbis floor0 inverse1 (floor0_inverse1). */

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

extern s32 oggpack_read(void *, s32);
extern void *fn_8022F8C4(s32 size);
extern s32 vorbis_book_decodev_set(Codebook *book, float *vec, void *opb, s32 n);
extern s32 _ilog(u32);
extern const float lbl_806517B8; /* 0.0f */

float *floor0_inverse1(register VorbisBlock *input, register Floor0Look *lookInput) {
    register Floor0Look *look;
    register VorbisBlock *vb;
    Floor0Info *info;
    s32 j, k;
    s32 ampraw;
    /* ASM: or (mr) preserves argument copies that this compiler changes to addi. */
    asm {
        or look, lookInput, lookInput
        or vb, input, input
    }
    info = lookInput->vi;
    ampraw = oggpack_read(vb->opb, info->ampbits);
    if (ampraw > 0) {
        float raw = (float)ampraw;
        float db = (float)info->ampdB;
        float maxval = (float)((1 << info->ampbits) - 1);
        float amp = raw / maxval * db;
        register s32 bits = _ilog(info->numbooks);
        s32 booknum;
        /* ASM: or (mr) keeps the argument copy, which C changes to addi. */
        asm { or bits, bits, bits }
        booknum = oggpack_read(vb->opb, bits);

        if (booknum != -1 && booknum < info->numbooks) {
            CodecSetup *ci = vb->vd->codec_setup;
            register Codebook *b = ci->fullbooks + info->books[booknum];
            double last = lbl_806517B8;
            s32 size = sizeof(float) * (look->m + 1);
            register float *lsp = fn_8022F8C4(size);
            j = 0;
            /* ASM: or (mr) preserves the pointer copy that C changes to addi. */
            asm { or lsp, lsp, lsp }

            for (; j < look->m; j += b->dim) {
                register Codebook *callBook;
                s32 dim = b->dim;
                float *vec = lsp + j;
                /* ASM: or (mr) preserves the argument copy that C changes to addi. */
                asm { or callBook, b, b }
                if (vorbis_book_decodev_set(callBook, vec, vb->opb, dim) == -1)
                    goto eop;
            }

            /* Restore each vector relative to the preceding vector's last value. */
            {
                register float *cursor;
                /* ASM: or (mr) keeps the cursor copy, which C changes to addi. */
                asm { or cursor, lsp, lsp }
                for (j = 0; j < look->m;) {
                    for (k = 0; k < b->dim; k++, j++, cursor++) {
                        *cursor += (float)last;
                    }
                    last = cursor[-1];
                }
            }

            lsp[look->m] = amp;
            return lsp;
        }
    }
eop:
    return 0;
}
