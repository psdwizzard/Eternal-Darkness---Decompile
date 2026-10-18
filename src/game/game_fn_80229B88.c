/* GXSetTevAlphaIn: configure a TEV stage's four alpha inputs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 pad4[0x170 - 4];
    u32 tevAlphaEnv[16];
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void GXSetTevAlphaIn(int stage, int a, int b, int c, int d)
{
    u32 *reg = &gx->tevAlphaEnv[stage];

    SET_FIELD(*reg, 3, 13, a);
    SET_FIELD(*reg, 3, 10, b);
    SET_FIELD(*reg, 3, 7, c);
    SET_FIELD(*reg, 3, 4, d);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = *reg;
    gx->bpSentNot = 0;
}
