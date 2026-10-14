typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u8 pad4[0x7C - 4];
    u32 lpSize;
} GXData;

extern GXData *gx;

typedef union {
    u8 byte;
    u32 word;
} GXFifo;

volatile GXFifo GXWGFifo : 0xCC008000;

/* GXSetLineWidth: set line width and the texture-coordinate offset. */
void fn_80226C18(u8 width, int texOffset)
{
    gx->lpSize = (gx->lpSize & ~0xFFUL) | (width & 0xFF);
    gx->lpSize = (gx->lpSize & ~0x70000UL) | ((u32)texOffset << 16);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->lpSize;
    gx->bpSentNot = 0;
}
