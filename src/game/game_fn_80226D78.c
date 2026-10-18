typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x204];
    u32 genMode;
} GXData;

extern GXData *gx;

typedef union {
    u8 byte;
    u32 word;
} GXFifo;
volatile GXFifo GXWGFifo : 0xCC008000;

/* GXSetCoPlanar: update coplanar mode using a masked BP register write. */
void GXSetCoPlanar(u8 enable)
{
    gx->genMode = (gx->genMode & ~0x80000UL) | ((u32)enable << 19);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = 0xFE080000;
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->genMode;
}
