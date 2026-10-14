/* GXSetScissorBoxOffset: load the SU scissor offset BP register (0x59)
 * with the half-pixel offsets biased by 342. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
} GXData;

extern GXData *gx;

typedef union {
    u8 u8;
    u32 u32;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void fn_8022BA20(s32 x_off, s32 y_off)
{
    u32 reg = 0;
    u32 hx;
    u32 hy;

    hx = (u32)(x_off + 342) >> 1;
    hy = (u32)(y_off + 342) >> 1;

    SET_REG_FIELD(reg, 10, 0, hx);
    SET_REG_FIELD(reg, 10, 10, hy);
    SET_REG_FIELD(reg, 8, 24, 0x59);

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    gx->bpSentNot = 0;
}
