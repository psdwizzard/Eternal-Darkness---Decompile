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

void fn_80226A28(void); /* __GXSetDirtyState */
void fn_80209AD4(void); /* PPCSync */

void fn_80226378(void)
{
    if (gx->dirtyState) {
        fn_80226A28();
    }
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    GXWGFifo.word = 0;
    fn_80209AD4();
}
