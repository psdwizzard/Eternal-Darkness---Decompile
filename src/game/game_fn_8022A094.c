/* GXSetZTexture: select the depth texture operation, format and bias. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int s32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void fn_8022A094(s32 operation, s32 format, s32 bias)
{
    u32 zenv0, zenv1;

    zenv0 = 0;
    SET_FIELD(zenv0, 24, 0, bias);
    SET_FIELD(zenv0, 8, 24, 0xF4);

    switch (format) {
    case 0x11:
        zenv1 = 0;
        break;
    case 0x13:
        zenv1 = 1;
        break;
    case 0x16:
        zenv1 = 2;
        break;
    default:
        zenv1 = 2;
        break;
    }
    SET_FIELD(zenv1, 2, 2, operation);
    SET_FIELD(zenv1, 8, 24, 0xF5);

    GXWGFifo.byte = 0x61;
    GXWGFifo.word = zenv0;
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = zenv1;
    gx->bpSentNot = 0;
}
