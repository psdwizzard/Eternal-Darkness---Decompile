typedef int BOOL;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSContext OSContext;
typedef void (*OSInterruptHandler)(s16 interrupt, OSContext *context);

typedef struct OSResetFunctionInfo OSResetFunctionInfo;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 __OSMaskInterrupts(u32 interrupts);
extern u32 __OSUnmaskInterrupts(u32 interrupts);
extern OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, OSInterruptHandler handler);
extern void OSRegisterResetFunction(OSResetFunctionInfo *info);

extern void RealMode_8020D670(void (*config)(void));
extern void Config24MB_8020D570(void);
extern void Config48MB_8020D5F0(void);
extern void MEMIntrruptHandler_8020D504(s16 interrupt, OSContext *context);
extern OSResetFunctionInfo ResetFunctionInfo_802FD8D0;

volatile u16 __MEMRegs[64] : 0xCC004000;

#define OSGetConsoleSimulatedMemSize() (*(u32 *)0x800000F0)
#define OSGetPhysicalMemSize() (*(u32 *)0x80000028)

#define OS_INTERRUPTMASK_MEM 0xF0000000
#define OS_INTERRUPTMASK_MEM_ADDRESS 0x08000000

void __OSInitMemoryProtection(void)
{
    u32 padding[12];
    register volatile u16 *regs;
    register u32 simulatedSize;
    register u32 bootInfo;
    register u32 physicalSize;
    register u32 currentSize;
    register BOOL enabled;
    register BOOL state;
    register u32 limit;
    register u16 zero;
    register OSInterruptHandler handler;
    register OSInterruptHandler argument;

    /* ASM: lis/lwz keep the boot-memory read after the register saves;
     * C schedules the address load into the stack prologue. */
    asm {
        lis bootInfo, 0x8000
        lwz simulatedSize, 0xF0(bootInfo)
    }
    state = OSDisableInterrupts();
    /* ASM: lis/cmplw/or/bgt preserve the comparison and saved-state copy
     * order; C schedules the copy before the comparison or uses addi. */
    asm {
        lis limit, 0x180
        cmplw simulatedSize, limit
        or enabled, state, state
        bgt largerMemory
    }
    RealMode_8020D670(Config24MB_8020D570);
    goto configured;
largerMemory:
    if (simulatedSize <= 0x3000000) {
        RealMode_8020D670(Config48MB_8020D5F0);
    }
configured:

    regs = __MEMRegs;
    zero = 0;
    /* ASM: sth preserves the memory-register base; C folds the address
     * into a different displacement for this first store. */
    asm { sth zero, 0x20(regs) }
    regs[8] = 0xFF;

    __OSMaskInterrupts(OS_INTERRUPTMASK_MEM);
    handler = MEMIntrruptHandler_8020D504;
    /* ASM: or (mr) keeps the callback copy; C emits addi-zero. */
    asm {
        or argument, handler, handler
    }
    __OSSetInterruptHandler(0, argument);
    /* ASM: or. (mr.) prevents callback-copy folding; C emits addi-zero.
     * The record bit is still different from retail. */
    asm {
        or. argument, handler, handler
    }
    __OSSetInterruptHandler(1, argument);
    /* ASM: or. (mr.) prevents callback-copy folding; C emits addi-zero.
     * The record bit is still different from retail. */
    asm {
        or. argument, handler, handler
    }
    __OSSetInterruptHandler(2, argument);
    /* ASM: or. (mr.) prevents callback-copy folding; C emits addi-zero.
     * The record bit is still different from retail. */
    asm {
        or. argument, handler, handler
    }
    __OSSetInterruptHandler(3, argument);
    /* ASM: or. (mr.) prevents callback-copy folding; C emits addi-zero.
     * The record bit is still different from retail. */
    asm {
        or. argument, handler, handler
    }
    __OSSetInterruptHandler(4, argument);
    OSRegisterResetFunction(&ResetFunctionInfo_802FD8D0);

    currentSize = OSGetConsoleSimulatedMemSize();
    physicalSize = OSGetPhysicalMemSize();
    if (currentSize < physicalSize && currentSize == 0x1800000) {
        regs[20] = 2;
    }

    __OSUnmaskInterrupts(OS_INTERRUPTMASK_MEM_ADDRESS);
    OSRestoreInterrupts(enabled);
}
