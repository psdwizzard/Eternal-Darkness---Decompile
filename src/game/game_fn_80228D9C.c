/* Invalidate both texture cache banks. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef union GXWGPipe {
    u8 byte;
    u32 word;
} GXWGPipe;

extern volatile GXWGPipe GXWGFifo : 0xCC008000;
extern void __GXFlushTextureState(void);

void GXInvalidateTexAll(void)
{
    __GXFlushTextureState();
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = 0x66001000;
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = 0x66001100;
    __GXFlushTextureState();
}
