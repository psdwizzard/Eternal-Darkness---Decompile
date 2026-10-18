typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u8 pad0[8];
    u32 cpEnable;
    u32 cpStatus;
} GXData;

extern GXData *gx;
extern volatile u16 *__cpReg;

/* __GXFifoReadDisable: stop the command processor reading the FIFO. */
void __GXFifoReadDisable(void)
{
    gx->cpEnable = gx->cpEnable & ~1UL;
    __cpReg[1] = gx->cpEnable;
}
