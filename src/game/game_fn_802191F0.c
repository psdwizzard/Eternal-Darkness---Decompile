typedef signed int s32;
typedef signed long long s64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

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

typedef void (*SICallback)(s32, u32, void*);
typedef void (*SITypeCallback)(s32, u32);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int);
extern u32 SIGetType(s32);
extern s32 SITransfer(s32, void*, u32, void*, u32, SICallback, s64);
extern s32 SIIsChanBusy(s32);
extern u32 SIGetStatus(s32);
extern u32 SIDisablePolling(u32);
extern s32 SIGetResponse(s32, void*);
extern u32 SIGetTypeAsync(s32, SITypeCallback);
extern void OSSetWirelessID(s32, u16);
extern void PADOriginUpdateCallback(s32, u32, void*);
extern void PADTypeAndStatusCallback(s32, u32);
extern void PADReceiveCheckCallback(s32, u32);
extern void* memset(void*, int, unsigned int);

extern s32 ResettingChan;
extern u32 Spec;
extern void (*MakeStatus)(s32, PadStatus*, u32*);
extern u32 CmdReadOrigin;
extern u32 EnabledBits;
extern u32 ResettingBits;
extern u32 RecalibrateBits;
extern u32 WaitingBits;
extern u32 CheckingBits;
extern u32 PendingBits;
extern PadStatus Origin[4];

static inline int ResetPending(PadStatus *origin, u32 pending)
{
    u32 result;
    int enabled2;
    enabled2 = OSDisableInterrupts();
    pending |= PendingBits;
    pending &= ~(WaitingBits | CheckingBits);

    ResettingBits |= pending;
    PendingBits = 0;
    result = ResettingBits & EnabledBits;
    EnabledBits &= ~pending;
    if (Spec == 4) {
        RecalibrateBits |= pending;
    }
    SIDisablePolling(result);
    if (ResettingChan == 0x20) {
        ResettingChan = __cntlzw(ResettingBits);
        if (ResettingChan != 32) {
            ResettingBits &= ~(0x80000000U >> ResettingChan);
            memset(&origin[ResettingChan], 0, 0xC);
            SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
        }
    }
    OSRestoreInterrupts(enabled2);
    return 1;
}

static inline void DisableChannel(s32 chan)
{
    int enabled2 = OSDisableInterrupts();
    u32 flags = 0x80000000U >> chan;
    SIDisablePolling(flags);
    EnabledBits &= ~flags;
    WaitingBits &= ~flags;
    CheckingBits &= ~flags;
    PendingBits &= ~flags;
    OSSetWirelessID(chan, 0);
    OSRestoreInterrupts(enabled2);
}

s32 PADRead(PadStatus* status)
{
    int enabled;
    s32 chan;
    u32 invalidChannels;
    u32 channelMask;
    u32 flags;
    u32 type;
    u32 response[2];
    /* Retain the eight reserved bytes in the retail stack frame. */
    u32 stackPadding[2];

    enabled = OSDisableInterrupts();
    invalidChannels = 0;
    channelMask = 0x80000000;
    for (chan = 0; chan < 4; chan++, status++) {
        flags = channelMask >> chan;

        if (PendingBits & flags) {
            ResetPending(Origin, 0);
            status->err = -2;
            memset(status, 0, 0xA);
        } else if ((ResettingBits & flags) || ResettingChan == chan) {
            status->err = -2;
            memset(status, 0, 0xA);
        } else if (!(EnabledBits & flags)) {
            status->err = -1;
            memset(status, 0, 0xA);
        } else if (SIIsChanBusy(chan)) {
            status->err = -3;
            memset(status, 0, 0xA);
        } else if (SIGetStatus(chan) & 8) {
            SIGetResponse(chan, response);
            if (WaitingBits & flags) {
                status->err = 0;
                memset(status, 0, 0xA);
                if (!(CheckingBits & flags)) {
                    CheckingBits |= flags;
                    SIGetTypeAsync(chan, PADReceiveCheckCallback);
                }
            } else {
                DisableChannel(chan);
                status->err = -1;
                memset(status, 0, 0xA);
            }
        } else {
            type = SIGetType(chan);
            if (!(type & 0x20000000)) {
                invalidChannels |= flags;
            }
            if (!SIGetResponse(chan, response)) {
                status->err = -3;
                memset(status, 0, 0xA);
            } else if (response[0] & 0x80000000) {
                status->err = -3;
                memset(status, 0, 0xA);
            } else {
                MakeStatus(chan, status, response);
                if (status->button & 0x2000) {
                    status->err = -3;
                    memset(status, 0, 0xA);
                    SITransfer(chan, &CmdReadOrigin, 1, &Origin[chan], 0xA,
                               PADOriginUpdateCallback, 0);
                } else {
                    status->err = 0;
                    status->button &= ~0x80;
                }
            }
        }
    }
    OSRestoreInterrupts(enabled);
    return invalidChannels;
}
