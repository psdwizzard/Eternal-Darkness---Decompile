/* GXCallDisplayList: flush pending GX state and issue a display-list call. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    union {
        struct {
            u16 vNumNot;
            u16 bpSentNot;
        } s;
        u32 notSent;
    } sent;
    u8 pad4[0x4F4 - 4];
    u32 dirtyState;
} GXData;

typedef union {
    u8 u8;
    u32 u32;
} PPCWGPipe;

extern GXData *gx;
volatile PPCWGPipe GXWGFifo : 0xCC008000;

void __GXSetDirtyState(void); /* __GXSetDirtyState */
void __GXSendFlushPrim(void); /* __GXSendFlushPrim */

void GXCallDisplayList(void *list, u32 size)
{
    if (gx->dirtyState != 0) {
        __GXSetDirtyState();
    }
    if (gx->sent.notSent == 0) {
        __GXSendFlushPrim();
    }
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u32 = (u32)list;
    GXWGFifo.u32 = size;
}
