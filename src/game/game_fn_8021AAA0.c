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
extern void fn_8021AB6C(s16, OSContext*);
extern void fn_8021ABE4(void);
extern ARCallback lbl_8064DB18;
extern u32 lbl_8064DB28;
extern u32 lbl_8064DB2C;
extern u32* lbl_8064DB30;
extern BOOL lbl_8064DB34;

volatile u16 __DSPRegs[] : 0xCC005000;

/* ARInit: initialize the ARAM allocator and its DMA interrupt handler. */
u32 fn_8021AAA0(u32* blockLengths, u32 numEntries)
{
    BOOL enabled;

    if (lbl_8064DB34 == 1) {
        return 0x4000;
    }
    enabled = OSDisableInterrupts();
    lbl_8064DB18 = 0;
    __OSSetInterruptHandler(6, fn_8021AB6C);
    __OSUnmaskInterrupts(0x02000000);
    lbl_8064DB2C = numEntries;
    lbl_8064DB28 = 0x4000;
    lbl_8064DB30 = blockLengths;
    __DSPRegs[0xD] = (__DSPRegs[0xD] & 0xFF) | (__DSPRegs[0xD] & ~0xFF);
    fn_8021ABE4();
    lbl_8064DB34 = 1;
    OSRestoreInterrupts(enabled);
    return lbl_8064DB28;
}
