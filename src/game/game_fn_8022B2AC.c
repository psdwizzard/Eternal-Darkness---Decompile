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
GXDisplayListState lbl_806426A0;
extern GXFifoObj *lbl_8064DBC8; /* OldCPUFifo */

#define GX32(o) (*(u32 *)(gx + (o)))
#define GX8(o) (*(u8 *)(gx + (o)))

void *memcpy(void *dst, const void *src, u32 n);
void fn_80226A28(void);              /* __GXSetDirtyState */
void fn_80224028(GXFifoObj *fifo);   /* GXSaveCPUFifo */
GXFifoBuffer *fn_80224640(void);        /* GXGetCPUFifo */
void GXSetCPUFifo(__GXFifoObj *fifo);

void fn_8022B2AC(void *list, u32 size) {
    GXFifoObj *cpuFifo = (GXFifoObj *)fn_80224640();

    if (GX32(0x4F4) != 0) {
        fn_80226A28();
    }
    if (GX8(0x4F1) != 0) {
        memcpy(lbl_806426A0.savedGXData, gx, 0x4F8);
    }
    lbl_806426A0.fifo.base = list;
    lbl_806426A0.fifo.top = (u8 *)list + size - 4;
    lbl_806426A0.fifo.size = size;
    lbl_806426A0.fifo.count = 0;
    lbl_806426A0.fifo.rdPtr = list;
    lbl_806426A0.fifo.wrPtr = list;
    GX8(0x4F0) = 1;
    fn_80224028(cpuFifo);
    lbl_8064DBC8 = cpuFifo;
    GXSetCPUFifo((__GXFifoObj *)&lbl_806426A0.fifo);
}
