typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

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

extern VITiming *lbl_8064DAA0;
volatile u16 __VIRegs[59] : 0xCC002000;

static inline u32 getCurrentHalfLine(void) {
    u32 hcount;
    u32 vcount0;
    u32 vcount;

    vcount = __VIRegs[22] & 0x7FF;
    do {
        vcount0 = vcount;
        hcount = __VIRegs[23] & 0x7FF;
        vcount = __VIRegs[22] & 0x7FF;
    } while (vcount0 != vcount);

    return ((vcount - 1) << 1) + ((hcount - 1) / lbl_8064DAA0->hlw);
}

/* Return whether the beam is in the first field. */
BOOL fn_8021818C(void) {
    u32 halfLine = getCurrentHalfLine();

    if (halfLine < lbl_8064DAA0->nhlines) {
        return 1;
    }
    return 0;
}
