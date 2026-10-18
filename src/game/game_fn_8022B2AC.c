/* GXBeginDisplayList: save the CPU FIFO (and optionally the GX state), then
 * redirect CPU writes into the caller's display-list buffer. */
typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;

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

/* Public FIFO storage and the byte-pointer view used by GXGetCPUFifo. */
typedef struct {
    u8 *base;
    u8 *top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    void *rdPtr;
    void *wrPtr;
    s32 count;
    u8 bind_cpu;
    u8 bind_gp;
    u8 wrap;
} __GXFifoObj;

typedef struct {
    u8 data[0x80];
} GXFifoStorage;

typedef union {
    __GXFifoObj fifo;
    GXFifoStorage storage;
} GXFifoBuffer;

typedef struct {
    GXFifoObj fifo;         /* DisplayListFifo */
    u8 savedGXData[0x4F8];  /* __savedGXdata */
} GXDisplayListState;

extern u8 *gx;
GXDisplayListState DisplayListFifo;
extern GXFifoObj *OldCPUFifo; /* OldCPUFifo */

#define GX32(o) (*(u32 *)(gx + (o)))
#define GX8(o) (*(u8 *)(gx + (o)))

void *memcpy(void *dst, const void *src, u32 n);
void __GXSetDirtyState(void);              /* __GXSetDirtyState */
void GXSaveCPUFifo(GXFifoObj *fifo);   /* GXSaveCPUFifo */
GXFifoBuffer *GXGetCPUFifo(void);        /* GXGetCPUFifo */
void GXSetCPUFifo(__GXFifoObj *fifo);

void GXBeginDisplayList(void *list, u32 size) {
    GXFifoObj *cpuFifo = (GXFifoObj *)GXGetCPUFifo();

    if (GX32(0x4F4) != 0) {
        __GXSetDirtyState();
    }
    if (GX8(0x4F1) != 0) {
        memcpy(DisplayListFifo.savedGXData, gx, 0x4F8);
    }
    DisplayListFifo.fifo.base = list;
    DisplayListFifo.fifo.top = (u8 *)list + size - 4;
    DisplayListFifo.fifo.size = size;
    DisplayListFifo.fifo.count = 0;
    DisplayListFifo.fifo.rdPtr = list;
    DisplayListFifo.fifo.wrPtr = list;
    GX8(0x4F0) = 1;
    GXSaveCPUFifo(cpuFifo);
    OldCPUFifo = cpuFifo;
    GXSetCPUFifo((__GXFifoObj *)&DisplayListFifo.fifo);
}
