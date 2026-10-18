/* Reset the bounding-box limits in the BP registers. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 pad0;
    u16 bpSentNot;
} GXData;

extern GXData *gx;

typedef union GXWGPipe {
    u8 byte;
    u32 word;
} GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void GXClearBoundingBox(void)
{
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = 0x550003FF;
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = 0x560003FF;
    gx->bpSentNot = 0;
}
