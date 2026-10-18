/* GXSetTevColorOp: configure a TEV stage's color operation. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 pad4[0x130 - 4];
    u32 tevColorEnv[16];
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void GXSetTevColorOp(int stage, int op, int bias, int scale, int clamp, int outReg)
{
    u32 *reg = &gx->tevColorEnv[stage];

    SET_FIELD(*reg, 1, 18, op & 1);
    if (op <= 1) {
        SET_FIELD(*reg, 2, 20, scale);
        SET_FIELD(*reg, 2, 16, bias);
    } else {
        SET_FIELD(*reg, 2, 20, (op >> 1) & 3);
        SET_FIELD(*reg, 2, 16, 3);
    }
    SET_FIELD(*reg, 1, 19, (u8)clamp);
    SET_FIELD(*reg, 2, 22, outReg);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = *reg;
    gx->bpSentNot = 0;
}
