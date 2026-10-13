/* fn_802188A4: PAD reset callback; enables the reset channel and starts the next reset. */
#include "src/game/types.h"

typedef struct PadStatus {
    u16 button;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerL;
    u8 triggerR;
    u8 analogA;
    u8 analogB;
    s8 err;
} PadStatus;

typedef void (*SITypeCallback)(s32 chan, u32 type);

extern s32 fn_80209140(s32 chan, u32 *data);          /* SIGetResponse */
extern void fn_80208ED4(s32 chan, u32 command);       /* SISetCommand */
extern void fn_80208F64(u32 poll);                    /* SIEnablePolling */
extern u32 fn_80209858(s32 chan, SITypeCallback callback);
extern void fn_8021897C(s32 chan, u32 type);
extern void *memset(void *dst, int value, unsigned long size);

extern PadStatus lbl_80641C20[4]; /* Origin */
extern s32 lbl_8064C428;          /* ResettingChan */
extern u32 lbl_8064C430;          /* AnalogMode */
extern u32 lbl_8064DAB4;          /* EnabledBits */
extern u32 lbl_8064DAB8;          /* ResettingBits */
extern u32 lbl_8064DAC0;          /* WaitingBits */

static void PADEnable(s32 chan)
{
    u32 cmd;
    u32 chanBit;
    u32 data[2];

    chanBit = 0x80000000U >> chan;
    lbl_8064DAB4 |= chanBit;
    fn_80209140(chan, data);
    cmd = lbl_8064C430 | 0x400000;
    fn_80208ED4(chan, cmd);
    fn_80208F64(lbl_8064DAB4);
}

static void DoReset(void)
{
    u32 chanBit;

    lbl_8064C428 = __cntlzw(lbl_8064DAB8);
    if (lbl_8064C428 != 32) {
        chanBit = 0x80000000U >> lbl_8064C428;
        lbl_8064DAB8 &= ~chanBit;
        memset(lbl_80641C20 + lbl_8064C428, 0, sizeof(PadStatus));
        fn_80209858(lbl_8064C428, fn_8021897C);
    }
}

void fn_802188A4(s32 unused, u32 type, void *context)
{
    if (!(type & 0xF)) {
        PADEnable(lbl_8064C428);
        lbl_8064DAC0 |= (0x80000000U >> lbl_8064C428);
    }
    DoReset();
}
