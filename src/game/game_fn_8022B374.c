/* GXEndDisplayList: close the display-list FIFO, restore the CPU FIFO and
 * the GX state saved by GXBeginDisplayList, and return the list size. */
typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef int BOOL;

typedef struct {
    void *base;
    void *top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    void *rdPtr;
    void *wrPtr;
    s32 count;
    u8 bind_cpu;
    u8 bind_gp;
    u8 wrap;
} GXFifoObj;

typedef struct {
    GXFifoObj fifo;         /* DisplayListFifo */
    u8 savedGXData[0x4F8];  /* __savedGXdata */
} GXDisplayListState;

extern u8 *gx;
extern volatile u32 *__piReg;
GXDisplayListState DisplayListFifo;
extern GXFifoObj *OldCPUFifo; /* OldCPUFifo */

#define GX32(o) (*(u32 *)(gx + (o)))
#define GX8(o) (*(u8 *)(gx + (o)))

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void *memcpy(void *dst, const void *src, u32 n);
void __GXSetDirtyState(void);              /* __GXSetDirtyState */
void __GXSaveCPUFifoAux(GXFifoObj *fifo);   /* __GXSaveCPUFifoAux */
void GXSetCPUFifo(GXFifoObj *fifo);

u32 GXEndDisplayList(void) {
    u32 ov;
    BOOL enabled;
    u32 bpMask;
    u32 reg;
    u32 pad[2]; /* unused; reproduces the original 0x20-byte frame */

    if (GX32(0x4F4) != 0) {
        __GXSetDirtyState();
    }
    reg = __piReg[5];
    ov = (reg >> 26) & 1;
    __GXSaveCPUFifoAux(&DisplayListFifo.fifo);
    GXSetCPUFifo(OldCPUFifo);
    if (GX8(0x4F1) != 0) {
        enabled = OSDisableInterrupts();
        bpMask = GX32(0x8);
        memcpy(gx, DisplayListFifo.savedGXData, 0x4F8);
        GX32(0x8) = bpMask;
        OSRestoreInterrupts(enabled);
    }
    GX8(0x4F0) = 0;
    if (!ov) {
        return DisplayListFifo.fifo.count;
    }
    return 0;
}
