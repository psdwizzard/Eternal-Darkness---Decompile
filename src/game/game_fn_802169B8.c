typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef int BOOL;

/* __VIRetraceHandler */

typedef struct OSContext {
    u32 gpr[32];
    u32 cr;
    u32 lr;
    u32 ctr;
    u32 xer;
    double fpr[32];
    u32 fpscr_pad;
    u32 fpscr;
    u32 srr0;
    u32 srr1;
    u16 mode;
    u16 state;
    u32 gqr[8];
    u32 psf_pad;
    double psf[32];
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
extern void OSWakeupThread(OSThreadQueue *queue);
extern u32 getCurrentFieldEvenOdd(void);
/* Runtime shift helpers. __shr2u receives the 64-bit value in r3/r4
 * and the shift in r5; __shl2i receives the same pair as explicit words. */
extern u64 fn_800F6218(u64 value, u32 shift);
extern u64 __shl2i(u32 hi, u32 lo, u32 shift);

extern VIState lbl_80641AC8;
extern u32 lbl_8064DA60;
extern u32 flushFlag;
extern OSThreadQueue retraceQueue;
extern VIRetraceCallback PreCB;
extern VIRetraceCallback PostCB;
extern u32 shdwChangeMode;
extern volatile u64 shdwChanged;
extern void *CurrTiming;
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

/* The shadow bank follows 59 registers and one padding halfword (0x78 bytes).
 * Keep the indexed base separate from the bank displacement. */
static inline u16 readShadowRegister(u16 *indexedRegs) {
    return indexedRegs[60];
}

static inline BOOL VISetRegs(VIState *vi) {
    int regIndex;
    register u16 *indexedRegs;

    if (!(shdwChangeMode == 1 && getCurrentFieldEvenOdd() == 0)) {
        while (shdwChanged) {
            regIndex = cntlzd(shdwChanged);
            indexedRegs = (u16 *)vi + regIndex;
            __VIRegs[regIndex] = readShadowRegister(indexedRegs);
            shdwChanged &= ~__shl2i(0, 1, 63 - regIndex);
        }
        shdwChangeMode = 0;
        CurrTiming = vi->timing;
        CurrTvMode_8064DAA4 = vi->tv;
        return 1;
    }
    return 0;
}

void __VIRetraceHandler(short interrupt, OSContext *context) {
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
    if (PreCB) {
        PreCB(lbl_8064DA60);
    }

    if (flushFlag) {
        if (VISetRegs(vi)) {
            flushFlag = 0;
            SIRefreshSamplingRate();
        }
    }

    if (PostCB) {
        OSClearContext(&exceptionContext);
        PostCB(lbl_8064DA60);
    }

    OSWakeupThread(&retraceQueue);
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
