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
extern u32 SIDisablePolling(u32);                /* SIDisablePolling */
extern void OSSetWirelessID(s32 chan, u16 id);  /* OSSetWirelessID */
extern void PADOriginUpdateCallback(s32, u32, void*);   /* PADOriginUpdateCallback */

extern u32 CmdReadOrigin;          /* CmdReadOrigin */
extern u32 EnabledBits;          /* EnabledBits */
extern u32 WaitingBits;          /* WaitingBits */
extern u32 CheckingBits;          /* CheckingBits */
extern u32 PendingBits;          /* PendingBits */
extern PadStatus Origin[4]; /* Origin */

static inline void PADDisable(s32 chan)
{
    u32 enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000U >> chan;
    SIDisablePolling(chanBit);
    EnabledBits &= ~chanBit;
    WaitingBits &= ~chanBit;
    CheckingBits &= ~chanBit;
    PendingBits &= ~chanBit;
    OSSetWirelessID(chan, 0);
    OSRestoreInterrupts(enabled);
}

/* PADReceiveCheckCallback: re-reads the origin of a wireless controller
 * that reported a valid fixed ID, or disables the channel otherwise. */
void PADReceiveCheckCallback(s32 chan, u32 type)
{
    u32 error;
    u32 chanBit;

    chanBit = 0x80000000U >> chan;
    if (EnabledBits & chanBit) {
        error = type & 0xFF;
        type &= ~0xFF;
        WaitingBits &= ~chanBit;
        CheckingBits &= ~chanBit;

        if (!(error & 0xF) && (type & 0x80000000) && (type & 0x00100000) &&
            (type & 0x40000000) && !(type & 0x04000000) &&
            !(type & 0x00080000) && !(type & 0x00040000)) {
            SITransfer(chan, &CmdReadOrigin, 1, &Origin[chan], 0xA,
                       PADOriginUpdateCallback, 0);
        } else {
            PADDisable(chan);
        }
    }
}
