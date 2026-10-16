/* fn_80218FE0: PADInit (stock Dolphin SDK pad/Pad.c) with PADReset and
 * DoReset inlined. */
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed long long s64;
typedef s64 OSTime;
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

typedef struct OSResetFunctionInfo OSResetFunctionInfo;
typedef void (*SITypeCallback)(s32, u32);

/* Pad.c .bss block starting at lbl_80641C10. */
typedef struct PadWork {
    u8 unk0[0x10];
    PadStatus Origin[4];
    u32 CmdProbeDevice[4];
} PadWork;

extern OSTime OSGetTime(void);
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL);
extern void OSRegisterResetFunction(OSResetFunctionInfo*);
extern void SIRefreshSamplingRate(void);
extern u32 fn_80209000(u32);
extern u32 fn_80209858(s32, SITypeCallback);
extern void fn_80219640(u32);
extern void fn_8021897C(s32, u32);
extern void* memset(void*, int, unsigned long);

extern PadWork lbl_80641C10;
extern OSResetFunctionInfo lbl_802FE9D8;
extern s32 lbl_8064C428;
extern u32 lbl_8064C434;
extern u32 lbl_8064D8D8;
extern BOOL lbl_8064DAB0;
extern u32 __PADSpec;
extern u32 lbl_8064DAB4;
extern u32 lbl_8064DAB8;
extern u32 lbl_8064DABC;
extern u32 lbl_8064DAC0;
extern u32 lbl_8064DAC4;
extern u32 lbl_8064DAC8;

/* Fixed low-memory SDK configuration word. */
extern u16 __OSWirelessPadFixMode : 0x800030E0;

static inline BOOL PADReset(PadStatus* origin, u32 mask)
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
            memset(&origin[lbl_8064C428], 0, sizeof(PadStatus));
            fn_80209858(lbl_8064C428, fn_8021897C);
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

BOOL fn_80218FE0(void)
{
    PadWork* work = &lbl_80641C10;
    s32 chan;

    if (lbl_8064DAB0) {
        return 1;
    }

    if (__PADSpec) {
        fn_80219640(__PADSpec);
    }

    lbl_8064DAB0 = 1;

    if (lbl_8064D8D8 != 0) {
        OSTime time = OSGetTime();
        time = ((time & 0xffff) + ((time >> 16) & 0xffff) +
               ((time >> 32) & 0xffff) + ((time >> 48) & 0xffff)) & 0x3fff;
        lbl_8064DABC = 0xF0000000;
        __OSWirelessPadFixMode = (u16)time;
    }

    for (chan = 0; chan < 4; ++chan) {
        work->CmdProbeDevice[chan] =
            (0x4D << 24) | (chan << 22) | ((__OSWirelessPadFixMode & 0x3fffu) << 8);
    }

    SIRefreshSamplingRate();
    OSRegisterResetFunction(&lbl_802FE9D8);

    return PADReset(work->Origin, 0xF0000000);
}
