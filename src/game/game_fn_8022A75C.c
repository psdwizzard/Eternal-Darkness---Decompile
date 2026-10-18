/* GXSetZMode: configure depth comparison and depth buffer updates. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 pad4[0x1D8 - 4];
    u32 zMode;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void GXSetZMode(u8 compareEnable, int compareFunction, u8 updateEnable)
{
    SET_FIELD(gx->zMode, 1, 0, compareEnable);
    SET_FIELD(gx->zMode, 3, 1, compareFunction);
    SET_FIELD(gx->zMode, 1, 4, updateEnable);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->zMode;
    gx->bpSentNot = 0;
}
