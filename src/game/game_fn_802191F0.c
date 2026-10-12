typedef signed int s32;
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

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern s32 SIGetType(s32);
extern s32 SITransfer(s32, void*, u32, void*, u32, SICallback, u32, u32);
extern s32 fn_802082D4(s32);
extern u32 fn_80208E58(s32);
extern void fn_80209000(u32);
extern s32 fn_80209140(s32, u32*);
extern u32 fn_80209858(s32, SITypeCallback);
extern void fn_8020EEA8(s32, s32, s32, s32, s32, s32);
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

s32 fn_802191F0(PadStatus* status)
{
    u32 enabled;
    u32 invalidChannels;
    s32 chan;
    u32 channelMask;

    enabled = OSDisableInterrupts();
    invalidChannels = 0;
    channelMask = 0x80000000;
    for (chan = 0; chan < 4; chan++) {
        u32 flags = channelMask >> chan;
        u32 type;

        if (lbl_8064DAC8 & flags) {
            u32 enabled2 = OSDisableInterrupts();
            u32 pending = lbl_8064DAC8 & ~(lbl_8064DAC0 | lbl_8064DAC4);
            u32 result;

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
                    memset((u8*)lbl_80641C20 + lbl_8064C428 * 0xC, 0, 0xC);
                    fn_80209858(lbl_8064C428, fn_8021897C);
                }
            }
            OSRestoreInterrupts(enabled2);
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
            u32 response;
            fn_80209140(chan, &response);
            if (lbl_8064DAC0 & flags) {
                status->err = 0;
                memset(status, 0, 0xA);
                if (!(lbl_8064DAC4 & flags)) {
                    lbl_8064DAC4 |= flags;
                    fn_80209858(chan, fn_80218CA8);
                }
            } else {
                u32 enabled2 = OSDisableInterrupts();
                u32 keep = ~flags;
                u32 oldPending;
                u32 oldUnk;
                u32 oldXfer;
                fn_80209000(flags);
                oldPending = lbl_8064DAB4 & keep;
                oldUnk = lbl_8064DAC0 & keep;
                oldXfer = lbl_8064DAC4 & keep;
                lbl_8064DAB4 = oldPending;
                lbl_8064DAC0 = oldUnk;
                lbl_8064DAC4 = oldXfer;
                lbl_8064DAC8 &= keep;
                fn_8020EEA8(chan, 0, oldXfer, oldUnk, oldPending, keep);
                OSRestoreInterrupts(enabled2);
                status->err = -1;
                memset(status, 0, 0xA);
            }
        } else {
            type = SIGetType(chan);
            if (!(type & 0x20000000)) {
                invalidChannels |= flags;
            }
            if (!fn_80209140(chan, &type) || (type & 0x80000000)) {
                status->err = -3;
                memset(status, 0, 0xA);
            } else {
                lbl_8064C438(chan, status, &type);
                if (status->button & 0x2000) {
                    status->err = -3;
                    memset(status, 0, 0xA);
                    SITransfer(chan, &lbl_8064C43C, 1, &lbl_80641C20[chan], 0xA,
                               fn_802187E4, 0, 0);
                } else {
                    status->err = 0;
                    status->button &= ~0x80;
                }
            }
        }
        status++;
    }
    OSRestoreInterrupts(enabled);
    return invalidChannels;
}
