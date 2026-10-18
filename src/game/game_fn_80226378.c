/* GXFlush: flush pending dirty state, pad the write-gather pipe, and sync. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x4F4];
    u32 dirtyState;
} GXData;
extern GXData *gx;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

void __GXSetDirtyState(void); /* __GXSetDirtyState */
void PPCSync(void); /* PPCSync */

void GXFlush(void)
{
    if (gx->dirtyState) {
        __GXSetDirtyState();
    }
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    PPCSync();
}
