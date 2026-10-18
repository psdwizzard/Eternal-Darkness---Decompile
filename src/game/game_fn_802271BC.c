typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef struct GXData {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad4[0x1E4 - 4];
    u32 cpDispSize;
    u8 pad1E8[0x1EC - 0x1E8];
    u32 cpDisp;
} GXData;

extern GXData *gx;
extern const f32 lbl_80651680; /* 256.0f */

unsigned int fn_800F5C54(double value);

typedef union { u8 byte; u32 word; } GXFifo;
volatile GXFifo GXWGFifo : 0xCC008000;

static inline u32 GetNumXfbLines(u32 efbHeight, u32 iScale)
{
    u32 count;
    u32 realHeight;
    u32 iScaleD;

    count = (efbHeight - 1) * 0x100;
    realHeight = (count / iScale) + 1;

    iScaleD = iScale;

    if (iScaleD > 0x80 && iScaleD < 0x100) {
        while (iScaleD % 2 == 0) {
            iScaleD /= 2;
        }

        if (efbHeight % iScaleD == 0) {
            realHeight++;
        }
    }

    if (realHeight > 0x400) {
        realHeight = 0x400;
    }

    return realHeight;
}

/* GXSetDispCopyYScale */
u32 GXSetDispCopyYScale(f32 vscale)
{
    u8 enable;
    u32 iScale;
    u32 ht;

    iScale = fn_800F5C54(lbl_80651680 / vscale) & 0x1FF;
    enable = (iScale != 0x100);

    GXWGFifo.byte = 0x61;
    GXWGFifo.word = iScale | 0x4E000000;
    gx->bpSentNot = 0;

    gx->cpDisp = (gx->cpDisp & ~0x400) | ((u32)enable << 10);
    ht = ((gx->cpDispSize >> 10) & 0x3FF) + 1;
    return GetNumXfbLines(ht, iScale);
}
