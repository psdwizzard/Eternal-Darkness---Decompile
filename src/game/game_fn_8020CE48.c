/* fn_8020CE48: __OSDispatchInterrupt (OSInterrupt.c) */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
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

static inline u32 InterruptBits(register u32 bits) {
    /* ASM: mr keeps a masked register value available for comparison;
     * the plain C zero test fuses the mask and comparison instructions. */
    asm {
        mr bits, bits
    }
    return bits;
}

void fn_8020CE48(u8 exception, register OSContext* exceptionContext) {
    register u32 intsr;
    register OSContext* context;
    register volatile u16* mem;
    register volatile u16* dsp;
    register volatile u32* exi1;
    register volatile u32* exi2;
    register u32 reg;
    register volatile u32* pi;
    register u32 piMask;
    register __OSInterrupt callInterrupt;
    register OSContext* callContext;
    register __OSInterruptHandler callHandler;
    OSInterruptMask cause;
    OSInterruptMask unmasked;
    OSInterruptMask* prio;
    register __OSInterruptHandler handler;
    register __OSInterrupt interrupt;

    /* ASM: mr/lis keep the saved context before the MMIO base setup;
     * C schedules the base load ahead of the register-save sequence. */
    asm {
        mr context, exceptionContext
        lis pi, 0xCC00
    }
    intsr = pi[0x3000 / 4];
    intsr &= ~0x00010000;

    /* ASM: cmplwi/beq preserve a separate zero comparison; C folds
     * a zero test into the record form of the preceding mask instruction. */
    asm {
        cmplwi intsr, 0
        beq loadContext
    }
    pi += 0x3000 / 4;
    /* ASM: lwz keeps the PI mask offset separate from the register base;
     * a C array access folds the base adjustment into the displacement. */
    asm {
        lwz piMask, 4(pi)
    }
    piMask = intsr & piMask;
    /* ASM: cmplwi/bne retain the separate unsigned zero comparison;
     * C combines it with the preceding AND when expressing this test. */
    asm {
        cmplwi piMask, 0
        bne dispatchInterrupt
    }
loadContext:
    OSLoadContext(context);

dispatchInterrupt:
    cause = 0;

    if ((intsr & 0x00000080) == 0x00000080) {
        mem = __MEMRegs;
        /* ASM: lhz keeps the status offset separate from the register
         * base; a C array access folds both into one load displacement. */
        asm {
            lhz reg, 0x1E(mem)
        }
        if (InterruptBits(reg & 0x1))
            cause |= 0x80000000;
        if ((reg & 0x2) == 0x2)
            cause |= 0x40000000;
        if ((reg & 0x4) == 0x4)
            cause |= 0x20000000;
        if ((reg & 0x8) == 0x8)
            cause |= 0x10000000;
        if ((reg & 0x10) == 0x10)
            cause |= 0x08000000;
    }

    if ((intsr & 0x00000040) == 0x00000040) {
        dsp = __DSPRegs;
        /* ASM: lhz keeps the status offset separate from the register
         * base; a C array access folds both into one load displacement. */
        asm {
            lhz reg, 0xA(dsp)
        }
        if (InterruptBits(reg & 0x8))
            cause |= 0x04000000;
        if ((reg & 0x20) == 0x20)
            cause |= 0x02000000;
        if ((reg & 0x80) == 0x80)
            cause |= 0x01000000;
    }

    if ((intsr & 0x00000020) == 0x00000020) {
        if ((__AIRegs[0] & 0x8) == 0x8)
            cause |= 0x00800000;
    }

    if ((intsr & 0x00000010) == 0x00000010) {
        reg = __EXIRegs[0];
        if ((reg & 0x2) == 0x2)
            cause |= 0x00400000;
        if ((reg & 0x8) == 0x8)
            cause |= 0x00200000;
        if ((reg & 0x800) == 0x800)
            cause |= 0x00100000;
        exi1 = __EXIRegs;
        /* ASM: lwz keeps the status offset separate from the register
         * base; a C array access folds both into one load displacement. */
        asm {
            lwz reg, 0x14(exi1)
        }
        if (InterruptBits(reg & 0x2))
            cause |= 0x00080000;
        if ((reg & 0x8) == 0x8)
            cause |= 0x00040000;
        if ((reg & 0x800) == 0x800)
            cause |= 0x00020000;
        exi2 = __EXIRegs;
        /* ASM: lwz keeps the status offset separate from the register
         * base; a C array access folds both into one load displacement. */
        asm {
            lwz reg, 0x28(exi2)
        }
        if (InterruptBits(reg & 0x2))
            cause |= 0x00010000;
        if ((reg & 0x8) == 0x8)
            cause |= 0x00008000;
    }

    if ((intsr & 0x00002000) == 0x00002000)
        cause |= 0x00000020;
    if ((intsr & 0x00001000) == 0x00001000)
        cause |= 0x00000040;
    if ((intsr & 0x00000400) == 0x00000400)
        cause |= 0x00001000;
    if ((intsr & 0x00000200) == 0x00000200)
        cause |= 0x00002000;
    if ((intsr & 0x00000100) == 0x00000100)
        cause |= 0x00000080;
    if ((intsr & 0x00000008) == 0x00000008)
        cause |= 0x00000800;
    if ((intsr & 0x00000004) == 0x00000004)
        cause |= 0x00000400;
    if ((intsr & 0x00000002) == 0x00000002)
        cause |= 0x00000200;
    if ((intsr & 0x00000800) == 0x00000800)
        cause |= 0x00004000;
    if ((intsr & 0x00000001) == 0x00000001)
        cause |= 0x00000100;

    unmasked = cause & ~(*(OSInterruptMask*)0x800000C4 | *(OSInterruptMask*)0x800000C8);
    if (unmasked >= 1U) {
        for (prio = lbl_802FD8A0;; ++prio) {
            if ((unmasked & *prio) >= 1U) {
                interrupt = (__OSInterrupt)__cntlzw(unmasked & *prio);
                break;
            }
        }

        handler = InterruptHandlerTable_8064D938[interrupt];
        if (handler) {
            if (4 < interrupt) {
                __OSLastInterrupt = interrupt;
                __OSLastInterruptTime = OSGetTime();
                __OSLastInterruptSrr0 = context->srr0;
            }
            OSDisableScheduler();
            /* ASM: mr/mr/mr keep the callback argument moves before
             * its target move; C schedules the target setup first. */
            asm {
                mr callInterrupt, interrupt
                mr callContext, context
                mr callHandler, handler
            }
            callHandler(callInterrupt, callContext);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }
    }

    OSLoadContext(context);
}
