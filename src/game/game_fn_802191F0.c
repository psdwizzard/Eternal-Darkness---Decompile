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
extern s32 fn_802082D4(s32);
extern u32 fn_80208E58(s32);
extern u32 fn_80209000(u32);
extern s32 fn_80209140(s32, void*);
extern u32 fn_80209858(s32, SITypeCallback);
extern void fn_8020EEA8(s32, u16);
extern void fn_802187E4(s32, u32, void*);
extern void fn_8021897C(s32, u32);
extern void fn_80218CA8(s32, u32);
extern void* memset(void*, int, unsigned int);

extern s32 lbl_8064C428;
extern u32 lbl_8064C434;
extern void (*lbl_8064C438)(s32, PadStatus*, u32*);
extern u32 lbl_8064C43C;
extern u32 lbl_8064DAB4;
extern u32 lbl_8064DAB8;
extern u32 lbl_8064DABC;
extern u32 lbl_8064DAC0;
extern u32 lbl_8064DAC4;
extern u32 lbl_8064DAC8;
extern PadStatus lbl_80641C20[4];

static inline int ResetPending(PadStatus *origin, u32 pending)
{
    u32 result;
    int enabled2;
    enabled2 = OSDisableInterrupts();
    pending |= lbl_8064DAC8;
    pending &= ~(lbl_8064DAC0 | lbl_8064DAC4);

    lbl_8064DAB8 |= pending;
    lbl_8064DAC8 = 0;
    result = lbl_8064DAB8 & lbl_8064DAB4;
    lbl_8064DAB4 &= ~pending;
    if (lbl_8064C434 == 4) {
        lbl_8064DABC |= pending;
    }
    fn_80209000(result);
    if (lbl_8064C428 == 0x20) {
        lbl_8064C428 = __cntlzw(lbl_8064DAB8);
        if (lbl_8064C428 != 32) {
            lbl_8064DAB8 &= ~(0x80000000U >> lbl_8064C428);
            memset(&origin[lbl_8064C428], 0, 0xC);
            fn_80209858(lbl_8064C428, fn_8021897C);
        }
    }
    OSRestoreInterrupts(enabled2);
    return 1;
}

static inline void DisableChannel(s32 chan)
{
    int enabled2 = OSDisableInterrupts();
    u32 flags = 0x80000000U >> chan;
    fn_80209000(flags);
    lbl_8064DAB4 &= ~flags;
    lbl_8064DAC0 &= ~flags;
    lbl_8064DAC4 &= ~flags;
    lbl_8064DAC8 &= ~flags;
    fn_8020EEA8(chan, 0);
    OSRestoreInterrupts(enabled2);
}

s32 fn_802191F0(PadStatus* status)
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

        if (lbl_8064DAC8 & flags) {
            ResetPending(lbl_80641C20, 0);
            status->err = -2;
            memset(status, 0, 0xA);
        } else if ((lbl_8064DAB8 & flags) || lbl_8064C428 == chan) {
            status->err = -2;
            memset(status, 0, 0xA);
        } else if (!(lbl_8064DAB4 & flags)) {
            status->err = -1;
            memset(status, 0, 0xA);
        } else if (fn_802082D4(chan)) {
            status->err = -3;
            memset(status, 0, 0xA);
        } else if (fn_80208E58(chan) & 8) {
            fn_80209140(chan, response);
            if (lbl_8064DAC0 & flags) {
                status->err = 0;
                memset(status, 0, 0xA);
                if (!(lbl_8064DAC4 & flags)) {
                    lbl_8064DAC4 |= flags;
                    fn_80209858(chan, fn_80218CA8);
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
            if (!fn_80209140(chan, response)) {
                status->err = -3;
                memset(status, 0, 0xA);
            } else if (response[0] & 0x80000000) {
                status->err = -3;
                memset(status, 0, 0xA);
            } else {
                lbl_8064C438(chan, status, response);
                if (status->button & 0x2000) {
                    status->err = -3;
                    memset(status, 0, 0xA);
                    SITransfer(chan, &lbl_8064C43C, 1, &lbl_80641C20[chan], 0xA,
                               fn_802187E4, 0);
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
