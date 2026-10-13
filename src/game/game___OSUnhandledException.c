/* __OSUnhandledException (0x8020C718, 512 bytes): Dolphin OS OSError.c.
 * Dispatches an exception to a registered error handler, or dumps the
 * context and diagnostic information and halts. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
typedef unsigned long long u64;
typedef u8 __OSException;
typedef u16 OSError;

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

typedef void (*OSErrorHandler)(OSError error, OSContext* context, ...);

extern void OSReport(const char* fmt, ...);
extern void OSLoadContext(OSContext* context);
extern void OSDumpContext(OSContext* context);
extern u64 OSGetTime(void);
extern s32 OSDisableScheduler(void);
extern s32 OSEnableScheduler(void);
extern void __OSReschedule(void);
extern void PPCHalt(void);

extern OSErrorHandler __OSErrorTable[];
extern s16 __OSLastInterrupt;
extern u32 __OSLastInterruptSrr0;
extern u64 __OSLastInterruptTime;

#define MSR_RI 0x00000002

extern volatile u16 __DSPRegs[] : 0xCC005000;
extern volatile u32 __DIRegs[] : 0xCC006000;

void __OSUnhandledException(__OSException exception, OSContext* context, u32 dsisr, u32 dar) {
    if (!(context->srr1 & MSR_RI)) {
        OSReport("Non-recoverable Exception %d", exception);
    } else {
        if (__OSErrorTable[exception]) {
            OSDisableScheduler();
            __OSErrorTable[exception](exception, context, dsisr, dar);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }

        if (exception == 8) {
            OSLoadContext(context);
        }

        OSReport("Unhandled Exception %d", exception);
    }

    OSReport("\n");
    OSDumpContext(context);
    OSReport("\nDSISR = 0x%08x                   DAR  = 0x%08x\n", dsisr, dar);
    OSReport("TB = 0x%016llx\n", OSGetTime());

    switch (exception) {
    case 2:
        OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access invalid address 0x%x (read from DAR)\n",
                 context->srr0, dar);
        break;
    case 3:
        OSReport("\nAttempted to fetch instruction from invalid address 0x%x (read from SRR0)\n", context->srr0);
        break;
    case 5:
        OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access unaligned address 0x%x (read from DAR)\n",
                 context->srr0, dar);
        break;
    case 6:
        OSReport("\nProgram exception : Possible illegal instruction/operation at or around 0x%x (read from SRR0)\n",
                 context->srr0, dar);
        break;
    case 15:
        OSReport("\n");
        OSReport("AI DMA Address =   0x%04x%04x\n", __DSPRegs[0x18], __DSPRegs[0x19]);
        OSReport("ARAM DMA Address = 0x%04x%04x\n", __DSPRegs[0x10], __DSPRegs[0x11]);
        OSReport("DI DMA Address =   0x%08x\n", __DIRegs[5]);
        break;
    }

    OSReport("\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n", __OSLastInterrupt, __OSLastInterruptSrr0,
             __OSLastInterruptTime);
    PPCHalt();
}
