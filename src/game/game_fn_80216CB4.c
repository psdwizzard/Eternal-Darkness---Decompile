typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct VITiming {
    u8 equ;
    u8 padding;
    u16 acv;
    u16 prbOdd, prbEven, psbOdd, psbEven;
    u8 bs[4];
    u16 be[4];
    u16 nhlines, hlw;
    u8 hsy, hcs, hce, hbe640;
    u16 hbs640;
    u8 hbeCCIR656;
    u16 hbsCCIR656;
} VITiming;

extern VITiming *fn_80216C24(s32 mode);
volatile u16 VI_REGS[] : 0xCC002000;

/* Initialize the video interface timing and enable the selected mode. */
void fn_80216CB4(s32 mode)
{
    volatile u32 delay;
    u32 tv = (u32)mode >> 2;
    u32 nonInter = mode & 2;
    VITiming *timing;
    u32 hbe;
    u32 hbs;
    u32 hcs;
    u32 nhlines;
    u32 hlw;

    *(u32 *)0x800000CC = tv;
    timing = fn_80216C24(mode);
    /* Hold the video interface in reset for the startup delay. */
    VI_REGS[1] = 2;
    delay = 0;
    if (delay < 1000) {
        while (delay < 1000) {
            delay += 8;
        }
    }
    VI_REGS[1] = 0;

    /* Pack the horizontal sync and blanking fields. */
    VI_REGS[3] = timing->hlw;
    hcs = timing->hcs;
    VI_REGS[2] = timing->hce | (hcs << 8);
    hbe = timing->hbe640;
    VI_REGS[5] = timing->hsy | (hbe << 7);
    hbs = timing->hbs640;
    VI_REGS[4] = (hbs << 1) & 0xFFFE;
    VI_REGS[0] = timing->equ;
    VI_REGS[7] = timing->prbOdd + timing->acv * 2 - 2;
    VI_REGS[6] = timing->psbOdd + 2;
    VI_REGS[9] = timing->prbEven + timing->acv * 2 - 2;
    VI_REGS[8] = timing->psbEven + 2;
    VI_REGS[11] = timing->bs[0] | (timing->be[0] << 5);
    VI_REGS[10] = timing->bs[2] | (timing->be[2] << 5);
    VI_REGS[13] = timing->bs[1] | (timing->be[1] << 5);
    VI_REGS[12] = timing->bs[3] | (timing->be[3] << 5);
    VI_REGS[36] = 0x2828;
    VI_REGS[27] = 1;
    VI_REGS[26] = 0x1001;
    /* Set the horizontal and vertical retrace interrupt positions. */
    nhlines = timing->nhlines;
    hlw = timing->hlw + 1;
    nhlines = (s32)nhlines / 2 + 1;
    VI_REGS[25] = hlw;
    VI_REGS[24] = nhlines | 0x1000;

    if (mode != 2 && mode != 3) {
        VI_REGS[1] = (nonInter << 2) | 1 | (tv << 8);
        VI_REGS[54] = 0;
    } else {
        VI_REGS[1] = (tv << 8) | 5;
        VI_REGS[54] = 1;
    }
}
