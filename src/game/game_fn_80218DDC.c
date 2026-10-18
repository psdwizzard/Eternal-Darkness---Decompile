typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int BOOL;

typedef struct PadStatus {
    u16 button;
    signed char stickX;
    signed char stickY;
    signed char substickX;
    signed char substickY;
    u8 triggerL;
    u8 triggerR;
    u8 analogA;
    u8 analogB;
    signed char err;
} PadStatus;

typedef void (*SITypeCallback)(s32, u32);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL);
extern u32 SIDisablePolling(u32);
extern u32 SIGetTypeAsync(s32, SITypeCallback);
extern void PADTypeAndStatusCallback(s32, u32);
extern void* memset(void*, int, unsigned long);

extern PadStatus Origin[4]; /* Origin */
extern s32 ResettingChan;         /* ResettingChan */
extern u32 Spec;         /* Spec */
extern u32 EnabledBits;         /* EnabledBits */
extern u32 ResettingBits;         /* ResettingBits */
extern u32 RecalibrateBits;         /* RecalibrateBits */
extern u32 WaitingBits;         /* WaitingBits */
extern u32 CheckingBits;         /* CheckingBits */
extern u32 PendingBits;         /* PendingBits */

/* PADReset: queue controller resets and begin the first pending channel. */
BOOL PADReset(u32 mask)
{
    BOOL enabled;
    u32 disableBits;

    enabled = OSDisableInterrupts();
    mask |= PendingBits;
    PendingBits = 0;
    mask &= ~(WaitingBits | CheckingBits);
    ResettingBits |= mask;
    disableBits = ResettingBits & EnabledBits;
    EnabledBits &= ~mask;
    if (Spec == 4) {
        RecalibrateBits |= mask;
    }
    SIDisablePolling(disableBits);
    if (ResettingChan == 32) {
        disableBits = ResettingBits;
        ResettingChan = __cntlzw(disableBits);
        if (ResettingChan != 32) {
            ResettingBits = disableBits & ~(0x80000000U >> ResettingChan);
            memset(&Origin[ResettingChan], 0, sizeof(PadStatus));
            SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
