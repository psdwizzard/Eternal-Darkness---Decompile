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

/* GXSetPointSize: set point size and the texture-coordinate offset. */
void fn_80226C70(u8 size, int texOffset)
{
    gx->lpSize = (gx->lpSize & ~0xFF00UL) | ((size << 8) & 0xFF00);
    gx->lpSize = (gx->lpSize & ~0x380000UL) | ((u32)texOffset << 19);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->lpSize;
    gx->bpSentNot = 0;
}
