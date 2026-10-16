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
    u16 mode;
    u16 state;
    u32 gqr[8];
    u32 psf_pad;
    double psf[32];
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
/* Interrupt diagnostics are updated asynchronously by the dispatcher. */
extern volatile s16 __OSLastInterrupt;
extern volatile u32 __OSLastInterruptSrr0;
extern volatile u64 __OSLastInterruptTime;

/* OSError.c diagnostic string pool. The first three formats belong to
 * the panic diagnostics; retaining them preserves the shared pool layout.
 * Each field includes the original four-byte alignment padding. */
typedef struct OSErrorMessages {
    char panic[0x18];
    char stack_header[0x28];
    char stack_frame[0x1C];
    char nonrecoverable[0x20];
    char unhandled[0x18];
    char status[0x34];
    char time[0x10];
    char invalid_address[0x60];
    char invalid_instruction[0x4C];
    char unaligned_address[0x64];
    char program[0x60];
    char audio_dma[0x20];
    char aram_dma[0x20];
    char disc_dma[0x1C];
    char last_interrupt[0x38];
} OSErrorMessages;

static OSErrorMessages diagnosticMessages = {
    " in \"%s\" on line %d.\n",
    "\nAddress:      Back Chain    LR Save\n",
    "0x%08x:   0x%08x    0x%08x\n",
    "Non-recoverable Exception %d",
    "Unhandled Exception %d",
    "\nDSISR = 0x%08x                   DAR  = 0x%08x\n",
    "TB = 0x%016llx\n",
    "\nInstruction at 0x%x (read from SRR0) attempted to access invalid address 0x%x (read from DAR)\n",
    "\nAttempted to fetch instruction from invalid address 0x%x (read from SRR0)\n",
    "\nInstruction at 0x%x (read from SRR0) attempted to access unaligned address 0x%x (read from DAR)\n",
    "\nProgram exception : Possible illegal instruction/operation at or around 0x%x (read from SRR0)\n",
    "AI DMA Address =   0x%04x%04x\n",
    "ARAM DMA Address = 0x%04x%04x\n",
    "DI DMA Address =   0x%08x\n",
    "\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n",
};

#define MSR_RI 0x00000002

extern volatile u16 __DSPRegs[] : 0xCC005000;
extern volatile u32 __DIRegs[] : 0xCC006000;

void __OSUnhandledException(__OSException exception, OSContext* context, u32 dsisr, u32 dar) {
    OSErrorMessages* msg = &diagnosticMessages;

    if (!(context->srr1 & MSR_RI)) {
        OSReport(msg->nonrecoverable, exception);
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

        OSReport(msg->unhandled, exception);
    }

    OSReport("\n");
    OSDumpContext(context);
    OSReport(msg->status, dsisr, dar);
    OSReport(msg->time, OSGetTime());

    switch (exception) {
    case 2:
        OSReport(msg->invalid_address, context->srr0, dar);
        break;
    case 3:
        OSReport(msg->invalid_instruction, context->srr0);
        break;
    case 5:
        OSReport(msg->unaligned_address, context->srr0, dar);
        break;
    case 6:
        OSReport(msg->program, context->srr0, dar);
        break;
    case 15:
        OSReport("\n");
        OSReport(msg->audio_dma, __DSPRegs[0x18], __DSPRegs[0x19]);
        OSReport(msg->aram_dma, __DSPRegs[0x10], __DSPRegs[0x11]);
        OSReport(msg->disc_dma, __DIRegs[5]);
        break;
    }

    OSReport(msg->last_interrupt, __OSLastInterrupt, __OSLastInterruptSrr0,
             __OSLastInterruptTime);
    PPCHalt();
}
