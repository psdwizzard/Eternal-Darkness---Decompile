typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

typedef struct {
    u8 pad0[8];
    u32 cpEnable;
    u32 cpStatus;
} GXData;

extern GXData *gx;
extern volatile u16 *__cpReg;

/* __GXFifoLink: link the CP FIFO to the CPU FIFO. */
void __GXFifoLink(u8 enable)
{
    BOOL link;

    if (enable) {
        link = 1;
    } else {
        link = 0;
    }
    gx->cpEnable = (gx->cpEnable & ~0x10UL) | (link << 4);
    __cpReg[1] = gx->cpEnable;
}
