typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
    u8 pad4[0x1DC - 4];
    u32 zControl;
} GXData;

extern GXData *gx;

typedef union GXWGPipe {
    u8 byte;
    u32 word;
} GXWGPipe;

extern volatile GXWGPipe GXWGFifo : 0xCC008000;

/* Send the cached depth-control register to the graphics FIFO. */
void GXPixModeSync(void)
{
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->zControl;
    gx->bpSentNot = 0;
}
