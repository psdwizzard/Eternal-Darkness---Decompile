/* GXSetFieldMode: set field rendering and half-aspect-ratio texture LOD. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 reserved[0x7C];
    u32 linePointWidth;
} GXData;
extern GXData *gx;
extern void __GXFlushTextureState(void);

typedef union GXWGPipe {
    u8 byte;
    u32 word;
} GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void GXSetFieldMode(u8 fieldMode, u8 halfAspectRatio)
{
    gx->linePointWidth = (gx->linePointWidth & ~(1UL << 22)) |
                         ((u32)halfAspectRatio << 22);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = gx->linePointWidth;
    __GXFlushTextureState();
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = 0x68000000 | (u32)fieldMode;
    __GXFlushTextureState();
}
