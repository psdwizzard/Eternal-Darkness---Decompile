typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 pad0;
    u16 bpSent;
    u8 pad4[0xB8 - 4];
    u32 suSsize[8];
} GXData;

extern GXData *gx;

typedef union {
    u8 byte;
    u32 word;
} GXFifo;
volatile GXFifo GXWGFifo : 0xCC008000;

/* GXSetTexCoordCylWrap: set cylindrical wrapping for a texture coordinate. */
void fn_80226CC4(int coord, u8 wrapS, u8 wrapT)
{
    gx->suSsize[coord] = (gx->suSsize[coord] & ~0x40000UL) | ((u32)wrapS << 18);
    gx->suSsize[coord] = (gx->suSsize[coord] & ~0x80000UL) | ((u32)wrapT << 19);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->suSsize[coord];
    gx->bpSent = 0;
}
