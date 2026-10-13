typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
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

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern s32 SITransfer(s32 chan, void* output, u32 outputBytes, void* input,
                      u32 inputBytes, SICallback callback, s64 delay);
extern u32 fn_80209000(u32);                /* SIDisablePolling */
extern void fn_8020EEA8(s32 chan, u16 id);  /* OSSetWirelessID */
extern void fn_802187E4(s32, u32, void*);   /* PADOriginUpdateCallback */

extern u32 lbl_8064C43C;          /* CmdReadOrigin */
extern u32 lbl_8064DAB4;          /* EnabledBits */
extern u32 lbl_8064DAC0;          /* WaitingBits */
extern u32 lbl_8064DAC4;          /* CheckingBits */
extern u32 lbl_8064DAC8;          /* PendingBits */
extern PadStatus lbl_80641C20[4]; /* Origin */

static inline void PADDisable(s32 chan)
{
    u32 enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000U >> chan;
    fn_80209000(chanBit);
    lbl_8064DAB4 &= ~chanBit;
    lbl_8064DAC0 &= ~chanBit;
    lbl_8064DAC4 &= ~chanBit;
    lbl_8064DAC8 &= ~chanBit;
    fn_8020EEA8(chan, 0);
    OSRestoreInterrupts(enabled);
}

/* PADReceiveCheckCallback: re-reads the origin of a wireless controller
 * that reported a valid fixed ID, or disables the channel otherwise. */
void fn_80218CA8(s32 chan, u32 type)
{
    u32 error;
    u32 chanBit;

    chanBit = 0x80000000U >> chan;
    if (lbl_8064DAB4 & chanBit) {
        error = type & 0xFF;
        type &= ~0xFF;
        lbl_8064DAC0 &= ~chanBit;
        lbl_8064DAC4 &= ~chanBit;

        if (!(error & 0xF) && (type & 0x80000000) && (type & 0x00100000) &&
            (type & 0x40000000) && !(type & 0x04000000) &&
            !(type & 0x00080000) && !(type & 0x00040000)) {
            SITransfer(chan, &lbl_8064C43C, 1, &lbl_80641C20[chan], 0xA,
                       fn_802187E4, 0);
        } else {
            PADDisable(chan);
        }
    }
}
