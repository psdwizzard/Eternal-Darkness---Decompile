typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x204];
    u32 genMode;
    u8 pad208[0x4F4 - 0x208];
    u32 dirtyState;
} GXData;

extern GXData *gx;

typedef union {
    u8 byte;
    u32 word;
} GXFifo;

volatile GXFifo GXWGFifo : 0xCC008000;

/* GXSetNumTexGens: set the number of generated texture coordinates. */
void fn_802262B8(u8 count)
{
    gx->genMode = (gx->genMode & ~0xF) | (u32)count;
    GXWGFifo.byte = 0x10;
    GXWGFifo.word = 0x103F;
    GXWGFifo.word = count;
    gx->dirtyState |= 4;
}
