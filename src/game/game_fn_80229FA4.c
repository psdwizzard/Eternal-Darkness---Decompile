/* GXSetTevSwapModeTable: program one swap table entry (two TEV ksel regs). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 pad4[0x1B0 - 4];
    u32 tevKsel[8];
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void fn_80229FA4(int table, int red, int green, int blue, int alpha)
{
    u32 *kreg;
    int index = table * 2;

    kreg = &gx->tevKsel[index];
    SET_FIELD(*kreg, 2, 0, red);
    SET_FIELD(*kreg, 2, 2, green);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = *kreg;

    kreg = &gx->tevKsel[index + 1];
    SET_FIELD(*kreg, 2, 0, blue);
    SET_FIELD(*kreg, 2, 2, alpha);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = *kreg;
    gx->bpSentNot = 0;
}
