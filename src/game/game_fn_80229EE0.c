typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad4[0x1B0 - 4];
    u32 tevKsel[8];
} GXData;

extern GXData *gx;

typedef union { u8 byte; u32 word; } GXFifo;
volatile GXFifo GXWGFifo : 0xCC008000;
#define GX_WRITE_U8(v) (GXWGFifo.byte = (u8)(v))
#define GX_WRITE_U32(v) (GXWGFifo.word = (u32)(v))

/* GXSetTevKColorSel: pick the konstant color selector for a TEV stage. */
void GXSetTevKAlphaSel(int stage, int sel)
{
    u32 *reg = &gx->tevKsel[stage >> 1];

    if (stage & 1) {
        *reg = (*reg & 0xFF07FFFF) | ((u32)sel << 19);
    } else {
        *reg = (*reg & 0xFFFFC1FF) | ((u32)sel << 9);
    }
    GX_WRITE_U8(0x61);
    GX_WRITE_U32(*reg);
    gx->bpSentNot = 0;
}
