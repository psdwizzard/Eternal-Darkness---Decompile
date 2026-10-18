typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef struct OSContext OSContext;
typedef void (*OSInterruptHandler)(s16, OSContext*);
typedef void (*ARCallback)(void);

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern OSInterruptHandler __OSSetInterruptHandler(s16, OSInterruptHandler);
extern u32 __OSUnmaskInterrupts(u32);
extern void __ARHandler(s16, OSContext*);
extern void __ARChecksize(void);
extern ARCallback __AR_Callback;
extern u32 __AR_StackPointer;
extern u32 __AR_FreeBlocks;
extern u32* __AR_BlockLength;
extern BOOL __AR_init_flag;

volatile u16 __DSPRegs[] : 0xCC005000;

/* ARInit: initialize the ARAM allocator and its DMA interrupt handler. */
u32 ARInit(u32* blockLengths, u32 numEntries)
{
    BOOL enabled;

    if (__AR_init_flag == 1) {
        return 0x4000;
    }
    enabled = OSDisableInterrupts();
    __AR_Callback = 0;
    __OSSetInterruptHandler(6, __ARHandler);
    __OSUnmaskInterrupts(0x02000000);
    __AR_FreeBlocks = numEntries;
    __AR_StackPointer = 0x4000;
    __AR_BlockLength = blockLengths;
    __DSPRegs[0xD] = (__DSPRegs[0xD] & 0xFF) | (__DSPRegs[0xD] & ~0xFF);
    __ARChecksize();
    __AR_init_flag = 1;
    OSRestoreInterrupts(enabled);
    return __AR_StackPointer;
}
