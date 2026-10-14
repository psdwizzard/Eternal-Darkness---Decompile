/* GXGetCPUFifo: return the currently bound CPU FIFO. */
typedef struct {
    unsigned char *base;
    unsigned char *top;
    unsigned long size;
    unsigned long hiWatermark;
    unsigned long loWatermark;
    void *rdPtr;
    void *wrPtr;
    long count;
    unsigned char bind_cpu;
    unsigned char bind_gp;
    unsigned char wrap;
} __GXFifoObj;

typedef struct {
    unsigned char data[0x80];
} GXFifoStorage;

typedef union {
    __GXFifoObj fifo;
    GXFifoStorage storage;
} GXFifoBuffer;

extern __GXFifoObj *lbl_8064DB90;

GXFifoBuffer *fn_80224640(void)
{
    return (GXFifoBuffer *)lbl_8064DB90;
}
