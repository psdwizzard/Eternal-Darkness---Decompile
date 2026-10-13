typedef int BOOL;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSContext OSContext;
typedef void (*OSInterruptHandler)(s16 interrupt, OSContext *context);

typedef struct OSResetFunctionInfo OSResetFunctionInfo;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void __OSMaskInterrupts(u32 interrupts);
extern void __OSUnmaskInterrupts(u32 interrupts);
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
    u32 simulatedSize;
    BOOL enabled;

    simulatedSize = OSGetConsoleSimulatedMemSize();
    enabled = OSDisableInterrupts();

    if (simulatedSize <= 0x1800000) {
        RealMode_8020D670(Config24MB_8020D570);
    } else if (simulatedSize <= 0x3000000) {
        RealMode_8020D670(Config48MB_8020D5F0);
    }

    __MEMRegs[16] = 0;
    __MEMRegs[8] = 0xFF;

    __OSMaskInterrupts(OS_INTERRUPTMASK_MEM);
    __OSSetInterruptHandler(0, MEMIntrruptHandler_8020D504);
    __OSSetInterruptHandler(1, MEMIntrruptHandler_8020D504);
    __OSSetInterruptHandler(2, MEMIntrruptHandler_8020D504);
    __OSSetInterruptHandler(3, MEMIntrruptHandler_8020D504);
    __OSSetInterruptHandler(4, MEMIntrruptHandler_8020D504);
    OSRegisterResetFunction(&ResetFunctionInfo_802FD8D0);

    if (OSGetConsoleSimulatedMemSize() < OSGetPhysicalMemSize() &&
        OSGetConsoleSimulatedMemSize() == 0x1800000) {
        __MEMRegs[20] = 2;
    }

    __OSUnmaskInterrupts(OS_INTERRUPTMASK_MEM_ADDRESS);
    OSRestoreInterrupts(enabled);
}
