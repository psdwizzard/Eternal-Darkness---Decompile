typedef unsigned long u32;
typedef short s16;
typedef struct OSContext OSContext;
typedef void (*OSInterruptHandler)(s16 interrupt, OSContext *context);

extern u32 __OSMaskInterrupts(u32 mask);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern OSInterruptHandler __OSSetInterruptHandler(s16 interrupt, OSInterruptHandler handler);
extern void fn_8022E050(s16 interrupt, OSContext *context);

void fn_8022E0A0(void)
{
    __OSMaskInterrupts(0x8000);
    __OSSetInterruptHandler(25, fn_8022E050);
    __OSUnmaskInterrupts(0x40);
}
