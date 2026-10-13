typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef int BOOL;

/* __VIRetraceHandler */

typedef struct OSContext {
    u8 data[0x2C8];
} OSContext;

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct VIState {
    u16 regs[59];
    u16 regsPadding;
    u16 shadowRegs[59];
    u16 shadowPadding;
    u16 posFields[16];
    s32 xfbMode;
    u32 nonInter;
    u32 tv;
    u8 pad11C[0x28];
    void *timing;
} VIState;

typedef void (*VIRetraceCallback)(u32 retraceCount);

extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
extern void SIRefreshSamplingRate(void);
extern void fn_802100F0(OSThreadQueue *queue);
extern u32 fn_8021818C(void);
/* runtime 64-bit shift helpers (__shr2u / __shl2i); the u64 occupies the
 * hi/lo argument register pair */
extern u64 fn_800F6218(u64 value, u32 shift);
extern u64 fn_800F61F4(u64 value, u32 shift);

extern VIState lbl_80641AC8;
extern u32 lbl_8064DA60;
extern u32 lbl_8064DA64;
extern OSThreadQueue lbl_8064DA68;
extern VIRetraceCallback lbl_8064DA70;
extern VIRetraceCallback lbl_8064DA74;
extern u32 lbl_8064DA90;
extern volatile u64 lbl_8064DA98;
extern void *lbl_8064DAA0;
extern u32 CurrTvMode_8064DAA4;

volatile u16 __VIRegs[59] : 0xCC002000;

static inline s32 cntlzd(u64 bit) {
    u32 hi, lo;
    s32 value;

    hi = (u32)fn_800F6218(bit, 32);
    lo = (u32)(bit & 0xFFFFFFFF);
    value = __cntlzw(hi);
    if (value < 32) {
        return value;
    }
    return 32 + __cntlzw(lo);
}

static inline BOOL VISetRegs(VIState *vi) {
    int regIndex;

    if (!(lbl_8064DA90 == 1 && fn_8021818C() == 0)) {
        while (lbl_8064DA98) {
            regIndex = cntlzd(lbl_8064DA98);
            __VIRegs[regIndex] = *(&vi->shadowRegs[0] + regIndex);
            lbl_8064DA98 &= ~fn_800F61F4(1, 63 - regIndex);
        }
        lbl_8064DA90 = 0;
        lbl_8064DAA0 = vi->timing;
        CurrTvMode_8064DAA4 = vi->tv;
        return 1;
    }
    return 0;
}

void fn_802169B8(short interrupt, OSContext *context) {
    OSContext exceptionContext;
    VIState *vi = &lbl_80641AC8;
    u16 reg;
    u32 inter = 0;

    reg = __VIRegs[24];
    if (reg & 0x8000) {
        __VIRegs[24] = (u16)(reg & ~0x8000);
        inter |= 1;
    }
    reg = __VIRegs[26];
    if (reg & 0x8000) {
        __VIRegs[26] = (u16)(reg & ~0x8000);
        inter |= 2;
    }
    reg = __VIRegs[28];
    if (reg & 0x8000) {
        __VIRegs[28] = (u16)(reg & ~0x8000);
        inter |= 4;
    }
    reg = __VIRegs[30];
    if (reg & 0x8000) {
        __VIRegs[30] = (u16)(reg & ~0x8000);
        inter |= 8;
    }

    if ((inter & 4) || (inter & 8)) {
        OSSetCurrentContext(context);
        return;
    }

    lbl_8064DA60++;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (lbl_8064DA70) {
        lbl_8064DA70(lbl_8064DA60);
    }

    if (lbl_8064DA64) {
        if (VISetRegs(vi)) {
            lbl_8064DA64 = 0;
            SIRefreshSamplingRate();
        }
    }

    if (lbl_8064DA74) {
        OSClearContext(&exceptionContext);
        lbl_8064DA74(lbl_8064DA60);
    }

    fn_802100F0(&lbl_8064DA68);
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
