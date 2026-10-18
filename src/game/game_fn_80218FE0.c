/* PADInit: PADInit (stock Dolphin SDK pad/Pad.c) with PADReset and
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
extern u32 SIDisablePolling(u32);
extern u32 SIGetTypeAsync(s32, SITypeCallback);
extern void PADSetSpec(u32);
extern void PADTypeAndStatusCallback(s32, u32);
extern void* memset(void*, int, unsigned long);

extern PadWork lbl_80641C10;
extern OSResetFunctionInfo lbl_802FE9D8;
extern s32 ResettingChan;
extern u32 Spec;
extern u32 __PADFixBits;
extern BOOL Initialized;
extern u32 __PADSpec;
extern u32 EnabledBits;
extern u32 ResettingBits;
extern u32 RecalibrateBits;
extern u32 WaitingBits;
extern u32 CheckingBits;
extern u32 PendingBits;

/* Fixed low-memory SDK configuration word. */
extern u16 __OSWirelessPadFixMode : 0x800030E0;

static inline BOOL PADReset(PadStatus* origin, u32 mask)
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
            memset(&origin[ResettingChan], 0, sizeof(PadStatus));
            SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
        }
    }
    OSRestoreInterrupts(enabled);
    return 1;
}

BOOL PADInit(void)
{
    PadWork* work = &lbl_80641C10;
    s32 chan;

    if (Initialized) {
        return 1;
    }

    if (__PADSpec) {
        PADSetSpec(__PADSpec);
    }

    Initialized = 1;

    if (__PADFixBits != 0) {
        OSTime time = OSGetTime();
        time = ((time & 0xffff) + ((time >> 16) & 0xffff) +
               ((time >> 32) & 0xffff) + ((time >> 48) & 0xffff)) & 0x3fff;
        RecalibrateBits = 0xF0000000;
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
