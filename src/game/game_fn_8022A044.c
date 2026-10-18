/* GXSetAlphaCompare: configure the two alpha tests and their combination. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void GXSetAlphaCompare(int compare0, int reference0, int operation, int compare1, int reference1)
{
    u32 reg = 0;

    SET_FIELD(reg, 8, 0, (u8)reference0);
    SET_FIELD(reg, 8, 8, (u8)reference1);
    SET_FIELD(reg, 3, 16, compare0);
    SET_FIELD(reg, 3, 19, compare1);
    SET_FIELD(reg, 2, 22, operation);
    SET_FIELD(reg, 8, 24, 0xF3);

    GXWGFifo.byte = 0x61;
    GXWGFifo.word = reg;
    gx->bpSentNot = 0;
}
