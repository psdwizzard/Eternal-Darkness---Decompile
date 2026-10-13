/* Recompute the BP texture-map mask for indirect stages (__GXUpdateBPMask). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 pad4[0x120 - 0x4];
    u32 iref;
    u32 bpMask;
    u8 pad128[0x204 - 0x128];
    u32 genMode;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 u8; u32 u32; float f32; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define GET_REG_FIELD(reg, size, shift) ((u32)((reg) >> (shift)) & ((1 << (size)) - 1))
#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void fn_80229874(void)
{
    u32 nBmp;
    u32 i;
    u32 tmap;
    u32 nBpmMask;

    nBmp = GET_REG_FIELD(gx->genMode, 3, 16);
    nBpmMask = 0;
    for (i = 0; i < nBmp; i++) {
        switch (i) {
        case 0:
            tmap = GET_REG_FIELD(gx->iref, 3, 0);
            break;
        case 1:
            tmap = GET_REG_FIELD(gx->iref, 3, 6);
            break;
        case 2:
            tmap = GET_REG_FIELD(gx->iref, 3, 12);
            break;
        case 3:
            tmap = GET_REG_FIELD(gx->iref, 3, 18);
            break;
        }
        nBpmMask |= 1 << tmap;
    }

    if ((u8)gx->bpMask != nBpmMask) {
        SET_REG_FIELD(gx->bpMask, 8, 0, nBpmMask);
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = gx->bpMask;
        gx->bpSentNot = 0;
    }
}
