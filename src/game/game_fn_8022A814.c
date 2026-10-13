/* GXSetPixelFmt: select the pixel/depth formats and update dependent BP state. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 pad4[0x1D4 - 4];
    u32 dstAlpha;
    u32 reserved1D8;
    u32 zControl;
    u8 pad1E0[0x204 - 0x1E0];
    u32 genMode;
    u8 pad208[0x4F4 - 0x208];
    u32 dirtyState;
} GXData;
extern GXData *gx;
extern u32 lbl_802FF2F8[];

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void fn_8022A814(int pixelFormat, int depthFormat)
{
    u32 oldZControl = gx->zControl;
    u8 multisample;

    SET_FIELD(gx->zControl, 3, 0, lbl_802FF2F8[pixelFormat]);
    SET_FIELD(gx->zControl, 3, 3, depthFormat);
    if (oldZControl != gx->zControl) {
        GXWGFifo.byte = 0x61;
        GXWGFifo.word = gx->zControl;
        if (pixelFormat == 2) {
            multisample = 1;
        } else {
            multisample = 0;
        }
        SET_FIELD(gx->genMode, 1, 9, multisample);
        gx->dirtyState |= 4;
    }
    if (lbl_802FF2F8[pixelFormat] == 4) {
        SET_FIELD(gx->dstAlpha, 2, 9, (pixelFormat - 4) & 3);
        SET_FIELD(gx->dstAlpha, 8, 24, 0x42);
        GXWGFifo.byte = 0x61;
        GXWGFifo.word = gx->dstAlpha;
    }
    gx->bpSentNot = 0;
}
