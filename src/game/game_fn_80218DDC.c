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
extern u32 fn_80209000(u32);
extern u32 fn_80209858(s32, SITypeCallback);
extern void fn_8021897C(s32, u32);
extern void* memset(void*, int, unsigned long);

extern PadStatus lbl_80641C20[4]; /* Origin */
extern s32 lbl_8064C428;         /* ResettingChan */
extern u32 lbl_8064C434;         /* Spec */
extern u32 lbl_8064DAB4;         /* EnabledBits */
extern u32 lbl_8064DAB8;         /* ResettingBits */
extern u32 lbl_8064DABC;         /* RecalibrateBits */
extern u32 lbl_8064DAC0;         /* WaitingBits */
extern u32 lbl_8064DAC4;         /* CheckingBits */
extern u32 lbl_8064DAC8;         /* PendingBits */

/* PADReset: queue controller resets and begin the first pending channel. */
BOOL fn_80218DDC(u32 mask)
{
    BOOL enabled;
    u32 disableBits;

    enabled = OSDisableInterrupts();
    mask |= lbl_8064DAC8;
    lbl_8064DAC8 = 0;
    mask &= ~(lbl_8064DAC0 | lbl_8064DAC4);
    lbl_8064DAB8 |= mask;
    disableBits = lbl_8064DAB8 & lbl_8064DAB4;
    lbl_8064DAB4 &= ~mask;
    if (lbl_8064C434 == 4) {
        lbl_8064DABC |= mask;
    }
    fn_80209000(disableBits);
    if (lbl_8064C428 == 32) {
        disableBits = lbl_8064DAB8;
        lbl_8064C428 = __cntlzw(disableBits);
        if (lbl_8064C428 != 32) {
            lbl_8064DAB8 = disableBits & ~(0x80000000U >> lbl_8064C428);
            memset(&lbl_80641C20[lbl_8064C428], 0, sizeof(PadStatus));
            fn_80209858(lbl_8064C428, fn_8021897C);
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}
