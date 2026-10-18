/* Set a controller's wireless ID in extended SRAM. */
typedef int BOOL;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct SramControlBlock {
    u8 sram[64];
    u32 offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
    void (*callback)(void);
} SramControlBlock;

typedef struct OSSramEx {
    u8 flashID[2][12];
    u32 wirelessKeyboardID;
    u16 wirelessPadID[4];
    u8 reserved[8];
} OSSramEx;

extern SramControlBlock Scb_80640E40;
extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern BOOL UnlockSram(BOOL commit, u32 offset);

static inline OSSramEx *LockSramEx(void)
{
    SramControlBlock *scb = &Scb_80640E40;
    BOOL enabled = OSDisableInterrupts();
    BOOL *locked;

    if (*(locked = &scb->locked)) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    scb->enabled = enabled;
    *locked = 1;
    return (OSSramEx *)(scb->sram + 0x14);
}

void OSSetWirelessID(s32 chan, u16 id)
{
    OSSramEx *sram = LockSramEx();

    if (sram->wirelessPadID[chan] != id) {
        sram->wirelessPadID[chan] = id;
        UnlockSram(1, 0x14);
    } else {
        UnlockSram(0, 0x14);
    }
}
