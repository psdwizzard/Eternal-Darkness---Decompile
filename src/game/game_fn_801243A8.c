typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;

typedef struct SkinWeight {
    f32 weight;
    u16 matrix;
    u16 pad;
} SkinWeight;

typedef struct SkinGroup {
    u16 count;
    u16 first;
} SkinGroup;

typedef struct SkinModel {
    u8 pad00[0xA];
    u16 count;
    u8 pad0C[0x20];
    SkinGroup* groups;
    u8 pad30[0x1C];
    SkinWeight* weights;
} SkinModel;

/* 3x4 matrices; the blend reads/writes 16 floats (8 float pairs) per matrix,
 * spilling one row into the following entry, which is later overwritten. */
typedef struct Mtx34 {
    f32 m[12];
} Mtx34;

extern Mtx34 lbl_804F02F0[];
extern Mtx34 lbl_804F3650[];
extern f32 lbl_80650114;

extern void DCFlushRange(void*, u32);

void fn_801243A8(SkinModel* model)
{
    s32 i;
    SkinGroup* group = model->groups;
    f32* out = lbl_804F3650[0].m;
    f32 one = lbl_80650114;
    f32 a0, a1, a2, a3, a4, a5, a6, a7;
    f32 a8, a9, a10, a11, a12, a13, a14, a15;

    for (i = 0; i < model->count; i++) {
        SkinWeight* w = &model->weights[group->first];
        s32 n = group->count - 2;
        f32 wt = w->weight;
        f32* src = lbl_804F02F0[w->matrix].m;

        if (one == wt) {
            a0 = src[0];   a1 = src[1];   a2 = src[2];   a3 = src[3];
            a4 = src[4];   a5 = src[5];   a6 = src[6];   a7 = src[7];
            a8 = src[8];   a9 = src[9];   a10 = src[10]; a11 = src[11];
            a12 = src[12]; a13 = src[13]; a14 = src[14]; a15 = src[15];
        } else {
            a0 = src[0] * wt;   a1 = src[1] * wt;
            a2 = src[2] * wt;   a3 = src[3] * wt;
            a4 = src[4] * wt;   a5 = src[5] * wt;
            a6 = src[6] * wt;   a7 = src[7] * wt;
            a8 = src[8] * wt;   a9 = src[9] * wt;
            a10 = src[10] * wt; a11 = src[11] * wt;
            a12 = src[12] * wt; a13 = src[13] * wt;
            a14 = src[14] * wt; a15 = src[15] * wt;
        }
        w++;
        if (group->count > 1) {
            do {
                wt = w->weight;
                src = lbl_804F02F0[w->matrix].m;
                a0 += src[0] * wt;   a1 += src[1] * wt;
                a2 += src[2] * wt;   a3 += src[3] * wt;
                a4 += src[4] * wt;   a5 += src[5] * wt;
                a6 += src[6] * wt;   a7 += src[7] * wt;
                a8 += src[8] * wt;   a9 += src[9] * wt;
                a10 += src[10] * wt; a11 += src[11] * wt;
                a12 += src[12] * wt; a13 += src[13] * wt;
                a14 += src[14] * wt; a15 += src[15] * wt;
                w++;
            } while (n-- != 0);
        }
        out[0] = a0;   out[1] = a1;   out[2] = a2;   out[3] = a3;
        out[4] = a4;   out[5] = a5;   out[6] = a6;   out[7] = a7;
        out[8] = a8;   out[9] = a9;   out[10] = a10; out[11] = a11;
        out[12] = a12; out[13] = a13; out[14] = a14; out[15] = a15;
        out += 12;
        group++;
    }
    DCFlushRange(lbl_804F3650, model->count * sizeof(Mtx34));
}
