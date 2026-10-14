/* GXSetDither: update the dither bit of the PE color mode 0 register and
 * send it down the BP pipe. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef u8 GXBool;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u8 pad[0x1D0 - 0x4];
    u32 cmode0;
} GXData;

extern GXData *gx;

typedef union {
    u8 u8;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void fn_8022A71C(GXBool dither)
{
    SET_REG_FIELD(gx->cmode0, 1, 4, dither);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->cmode0;
    gx->bpSentNot = 0;
}
