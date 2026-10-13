/* Construct the sorted posts and prediction neighbors for a Vorbis floor. */
#include "src/game/types.h"

typedef struct FloorInfo {
    s32 partitions;
    u8 partitionclass[31];
    u8 class_dim[16];
    u8 class_subs[16];
    u8 class_book[16];
    u8 class_subbook[16][8];
    s32 mult;
    s32 postlist[65];
} FloorInfo;

typedef struct FloorLook {
    u16 forward_index[65];
    u8 hineighbor[63];
    u8 loneighbor[63];
    s32 posts;
    s32 n;
    s32 quant_q;
    FloorInfo *info;
    long phrasebits;
    long postbits;
    long frames;
} FloorLook;

extern void *fn_8022F780(s32 size);
extern void fn_800FBE38(void *base, unsigned long count, unsigned long size,
                       int (*compare)(const void *, const void *));
extern int fn_80231C9C(const void *, const void *);

FloorLook *fn_8023185C(void *dsp, void *mode, void *floor_info)
{
    FloorInfo *source = (FloorInfo *)floor_info;
    FloorLook *look = fn_8022F780(sizeof(FloorLook));
    long count = 0;
    s32 *sort[65];
    long i, j;

    look->info = source;
    look->n = source->postlist[1];
    for (i = 0; i < source->partitions; i++) {
        count += source->class_dim[source->partitionclass[i]];
    }
    look->posts = count + 2;
    /* Fill complete groups of eight, then the remaining post pointers. */
    i = 0;
    if (count + 2 > 0) {
        if (count + 2 > 8) {
            s32 *post = source->postlist;
            s32 blocks = (unsigned long)(count + 1) >> 3;
            s32 **out = sort;
            while (--blocks >= 0) {
                out[0] = post;
                out[1] = post + 1;
                out[2] = post + 2;
                out[3] = post + 3;
                out[4] = post + 4;
                out[5] = post + 5;
                out[6] = post + 6;
                out[7] = post + 7;
                out += 8;
                post += 8;
                i += 8;
            }
        }
        if (i < count + 2) {
            do {
                sort[i] = &source->postlist[i];
            } while (++i < count + 2);
        }
    }
    fn_800FBE38(sort, count + 2, sizeof(*sort), fn_80231C9C);
    for (i = 0; i < count + 2; i++) {
        look->forward_index[i] = sort[i] - source->postlist;
    }
    switch (source->mult) {
    case 1: look->quant_q = 256; break;
    case 2: look->quant_q = 128; break;
    case 3: look->quant_q = 86; break;
    case 4: look->quant_q = 64; break;
    }
    /* Predict each new post from the closest earlier post on either side. */
    for (i = 0; i < count; i++) {
        u8 lo = 0;
        u8 hi = 1;
        s32 lx = 0;
        s32 hx = look->n;
        s32 current = source->postlist[i + 2];
        for (j = 0; j < i + 2; j++) {
            s32 x = source->postlist[j];
            if (x > lx && x < current) {
                lo = j;
                lx = x;
            }
            if (x < hx && x > current) {
                hi = j;
                hx = x;
            }
        }
        look->loneighbor[i] = lo;
        look->hineighbor[i] = hi;
    }
    return look;
}
