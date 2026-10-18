typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

typedef struct GXData {
    u16 vNumNot;
    u16 bpSentNot;
    u8 pad4[0x4F4 - 4];
    u32 dirtyState;
} GXData;

extern GXData *gx;

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void __GXSetDirtyState(void); /* __GXSetDirtyState */
void PPCSync(void); /* PPCSync */

typedef union {
    u8 byte;
    u32 word;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

/* Queue a draw-sync token, then flush the write-gather pipe. */
void GXSetDrawSync(u16 token)
{
    u32 command;
    BOOL enabled = OSDisableInterrupts();

    command = 0x48000000 | token;
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = command;
    command = (command & ~0xFFFF) | token;
    command = (command & 0x00FFFFFF) | 0x47000000;
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = command;

    if (gx->dirtyState != 0) {
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
    OSRestoreInterrupts(enabled);
    gx->bpSentNot = 0;
}
