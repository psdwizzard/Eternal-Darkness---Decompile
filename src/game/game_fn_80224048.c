typedef unsigned char u8;
typedef unsigned short u16;
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

extern volatile u16 *__cpReg;
extern volatile u32 *__piReg;
extern u8 lbl_8064DB9C; /* CPGPLinked */

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
void fn_80226378(void);

/* __GXSaveCPUFifoAux */
void fn_80224048(GXFifoObj *realFifo)
{
    BOOL enabled = OSDisableInterrupts();

    fn_80226378();
    realFifo->base = (void *)(__piReg[3] + 0x80000000);
    realFifo->top = (void *)(__piReg[4] + 0x80000000);
    realFifo->wrPtr = (void *)((__piReg[5] & ~0x04000000) + 0x80000000);
    if (lbl_8064DB9C) {
        u32 temp = __cpReg[29] << 16;
        temp |= __cpReg[28];
        realFifo->rdPtr = (void *)(temp + 0x80000000);
        {
            u32 temp2 = __cpReg[25] << 16;
            temp2 |= __cpReg[24];
            realFifo->count = temp2;
        }
    } else {
        realFifo->count = (u8 *)realFifo->wrPtr - (u8 *)realFifo->rdPtr;
        if (realFifo->count < 0) {
            realFifo->count += realFifo->size;
        }
    }
    OSRestoreInterrupts(enabled);
}
