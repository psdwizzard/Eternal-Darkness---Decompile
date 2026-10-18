typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    unsigned char pad0[8];
    u32 cpEnable;
} GXData;

extern GXData *gx;
extern volatile u16 *__cpReg;

/* __GXFifoReadEnable: enable the command processor to read the FIFO. */
void __GXFifoReadEnable(void)
{
    gx->cpEnable = (gx->cpEnable & ~1UL) | 1;
    __cpReg[1] = gx->cpEnable;
}
