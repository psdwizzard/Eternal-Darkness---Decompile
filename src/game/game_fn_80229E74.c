/* GXSetTevKColorSel: select the constant color for a TEV stage. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 reserved4[0x1B0 - 4];
    u32 tevKSel[8];
} GXData;

extern GXData *gx;
typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void fn_80229E74(int stage, int selection)
{
    u32 *reg = &gx->tevKSel[stage >> 1];

    if (stage & 1) {
        *reg = (*reg & ~(0x1FU << 14)) | ((u32)selection << 14);
    } else {
        *reg = (*reg & ~(0x1FU << 4)) | ((u32)selection << 4);
    }

    GXWGFifo.byte = 0x61;
    GXWGFifo.word = *reg;
    gx->bpSentNot = 0;
}
