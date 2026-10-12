/* fn_8020CE48: __OSDispatchInterrupt (OSInterrupt.c) */

typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef short s16;
typedef unsigned long long u64;

typedef s16 __OSInterrupt;
typedef u32 OSInterruptMask;

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
} OSContext;

typedef void (*__OSInterruptHandler)(__OSInterrupt interrupt, OSContext* context);

extern void OSLoadContext(OSContext* context);
extern u64 OSGetTime(void);
extern s32 OSDisableScheduler(void);
extern s32 OSEnableScheduler(void);
extern void __OSReschedule(void);

extern __OSInterruptHandler* InterruptHandlerTable_8064D938;
extern __OSInterrupt __OSLastInterrupt;
extern u32 __OSLastInterruptSrr0;
extern u64 __OSLastInterruptTime;
extern OSInterruptMask lbl_802FD8A0[];

#define __PIRegs ((volatile u32*)0xCC003000)
#define __MEMRegs ((volatile u16*)0xCC004000)
#define __DSPRegs ((volatile u16*)0xCC005000)
#define __EXIRegs ((volatile u32*)0xCC006800)
#define __AIRegs ((volatile u32*)0xCC006C00)

static inline __OSInterruptHandler __OSGetInterruptHandler(__OSInterrupt interrupt) {
    return InterruptHandlerTable_8064D938[interrupt];
}

void fn_8020CE48(s32 exception, OSContext* context) {
    u32 intsr;
    u32 reg;
    OSInterruptMask cause;
    OSInterruptMask unmasked;
    OSInterruptMask* prio;
    __OSInterruptHandler handler;
    __OSInterrupt interrupt;

    intsr = __PIRegs[0];
    intsr &= ~0x00010000;

    if (intsr == 0 || (intsr & __PIRegs[1]) == 0) {
        OSLoadContext(context);
    }

    cause = 0;

    if (intsr & 0x00000080) {
        reg = __MEMRegs[15];
        if (reg & 0x1)
            cause |= 0x80000000;
        if (reg & 0x2)
            cause |= 0x40000000;
        if (reg & 0x4)
            cause |= 0x20000000;
        if (reg & 0x8)
            cause |= 0x10000000;
        if (reg & 0x10)
            cause |= 0x08000000;
    }

    if (intsr & 0x00000040) {
        reg = __DSPRegs[5];
        if (reg & 0x8)
            cause |= 0x04000000;
        if (reg & 0x20)
            cause |= 0x02000000;
        if (reg & 0x80)
            cause |= 0x01000000;
    }

    if (intsr & 0x00000020) {
        reg = __AIRegs[0];
        if (reg & 0x8)
            cause |= 0x00800000;
    }

    if (intsr & 0x00000010) {
        reg = __EXIRegs[0];
        if (reg & 0x2)
            cause |= 0x00400000;
        if (reg & 0x8)
            cause |= 0x00200000;
        if (reg & 0x800)
            cause |= 0x00100000;
        reg = __EXIRegs[5];
        if (reg & 0x2)
            cause |= 0x00080000;
        if (reg & 0x8)
            cause |= 0x00040000;
        if (reg & 0x800)
            cause |= 0x00020000;
        reg = __EXIRegs[10];
        if (reg & 0x2)
            cause |= 0x00010000;
        if (reg & 0x8)
            cause |= 0x00008000;
    }

    if (intsr & 0x00002000)
        cause |= 0x00000020;
    if (intsr & 0x00001000)
        cause |= 0x00000040;
    if (intsr & 0x00000400)
        cause |= 0x00001000;
    if (intsr & 0x00000200)
        cause |= 0x00002000;
    if (intsr & 0x00000100)
        cause |= 0x00000080;
    if (intsr & 0x00000008)
        cause |= 0x00000800;
    if (intsr & 0x00000004)
        cause |= 0x00000400;
    if (intsr & 0x00000002)
        cause |= 0x00000200;
    if (intsr & 0x00000800)
        cause |= 0x00004000;
    if (intsr & 0x00000001)
        cause |= 0x00000100;

    unmasked = cause & ~(*(OSInterruptMask*)0x800000C4 | *(OSInterruptMask*)0x800000C8);
    if (unmasked) {
        for (prio = lbl_802FD8A0;; ++prio) {
            if (unmasked & *prio) {
                interrupt = (__OSInterrupt)__cntlzw(unmasked & *prio);
                break;
            }
        }

        handler = __OSGetInterruptHandler(interrupt);
        if (handler) {
            if (4 < interrupt) {
                __OSLastInterrupt = interrupt;
                __OSLastInterruptTime = OSGetTime();
                __OSLastInterruptSrr0 = context->srr0;
            }
            OSDisableScheduler();
            handler(interrupt, context);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }
    }

    OSLoadContext(context);
}
