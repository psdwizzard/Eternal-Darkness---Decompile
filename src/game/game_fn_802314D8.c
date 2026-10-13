#include "src/game/types.h"

/* Vorbis floor1 inverse1 (unpack floor posts from the packet). */

typedef struct Codebook {
    u8 pad[0x1C];
} Codebook;

typedef struct CodecSetup {
    u8 pad[0xC];
    Codebook *fullbooks;
} CodecSetup;

typedef struct DspState {
    u8 pad[0x48];
    CodecSetup *codecSetup;
} DspState;

typedef struct VorbisBlock {
    u8 pad0[0x4];
    u8 opb[0x34];
    DspState *vd;
} VorbisBlock;

typedef struct Floor1Info {
    s32 partitions;
    u8 partitionclass[31];
    u8 class_dim[16];
    u8 class_subs[16];
    u8 class_book[16];
    s8 class_subbook[16][8];
    s32 mult;
    s32 postlist[65];
} Floor1Info;

typedef struct Floor1Look {
    u8 sorted_index[65];
    u8 forward_index[65];
    u8 hineighbor[63];
    u8 loneighbor[63];
    s32 posts;
    s32 n;
    s32 quant_q;
    Floor1Info *vi;
} Floor1Look;

extern s32 fn_8022E868(void *, s32);
extern void *fn_8022F8C4(s32 size);
extern s32 fn_80230718(Codebook *book, void *opb);

static s32 ilog(u32 v) {
    s32 ret = 0;
    while (v) {
        ret++;
        v >>= 1;
    }
    return ret;
}

static s32 render_point(s32 x0, s32 x1, s32 y0, s32 y1, s32 x) {
    y0 &= 0x7FFF;
    y1 &= 0x7FFF;
    {
        s32 dy = y1 - y0;
        s32 adx = x1 - x0;
        s32 ady = __abs(dy);
        s32 err = ady * (x - x0);
        s32 off = err / adx;
        s32 y = y0 + off;
        if (dy < 0) {
            y = y0 - off;
        }
        return y;
    }
}

s32 *fn_802314D8(VorbisBlock *vb, Floor1Look *look) {
    Floor1Info *info = look->vi;
    Codebook *books = vb->vd->codecSetup->fullbooks;
    s32 i, j, k;

    if (fn_8022E868(vb->opb, 1) == 1) {
        s32 *fit_value = (s32 *)fn_8022F8C4(look->posts * sizeof(s32));

        fit_value[0] = fn_8022E868(vb->opb, ilog(look->quant_q - 1));
        fit_value[1] = fn_8022E868(vb->opb, ilog(look->quant_q - 1));

        for (i = 0, j = 2; i < info->partitions; i++) {
            s32 classv = info->partitionclass[i];
            s32 cdim = info->class_dim[classv];
            s32 csubbits = info->class_subs[classv];
            s32 csub = 1 << csubbits;
            s32 cval = 0;

            if (csubbits) {
                cval = fn_80230718(books + info->class_book[classv], vb->opb);
                if (cval == -1) goto eop;
            }

            for (k = 0; k < cdim; k++) {
                s32 book = info->class_subbook[classv][cval & (csub - 1)];
                cval >>= csubbits;
                if (book >= 0) {
                    if ((fit_value[j + k] = fn_80230718(books + book, vb->opb)) == -1) goto eop;
                } else {
                    fit_value[j + k] = 0;
                }
            }
            j += cdim;
        }

        for (i = 2; i < look->posts; i++) {
            s32 predicted = render_point(info->postlist[look->loneighbor[i - 2]],
                                         info->postlist[look->hineighbor[i - 2]],
                                         fit_value[look->loneighbor[i - 2]],
                                         fit_value[look->hineighbor[i - 2]],
                                         info->postlist[i]);
            s32 hiroom = look->quant_q - predicted;
            s32 loroom = predicted;
            s32 room;
            s32 val;

            room = loroom;
            if (hiroom < loroom) {
                room = hiroom;
            }
            room <<= 1;
            val = fit_value[i];

            if (val) {
                if (val >= room) {
                    if (hiroom > loroom) {
                        val = val - loroom;
                    } else {
                        val = -1 - (val - hiroom);
                    }
                } else {
                    if (val & 1) {
                        val = -((val + 1) >> 1);
                    } else {
                        val >>= 1;
                    }
                }

                fit_value[i] = val + predicted;
                fit_value[look->loneighbor[i - 2]] &= 0x7FFF;
                fit_value[look->hineighbor[i - 2]] &= 0x7FFF;
            } else {
                fit_value[i] = predicted | 0x8000;
            }
        }

        return fit_value;
    }
eop:
    return 0;
}
