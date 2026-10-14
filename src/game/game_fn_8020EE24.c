/* Get a controller's wireless ID in extended SRAM. */
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
extern BOOL fn_8020E88C(BOOL commit, u32 offset);

static inline void *LockSram(u32 offset)
{
    SramControlBlock *scb = &Scb_80640E40;
    BOOL enabled = OSDisableInterrupts();
    BOOL *locked = &scb->locked;

    if (scb->locked) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    scb->enabled = enabled;
    *locked = 1;
    return scb->sram + offset;
}

static inline OSSramEx *LockSramEx(void)
{
    return (OSSramEx *)LockSram(0x14);
}

static inline BOOL UnlockSramEx(BOOL commit)
{
    return fn_8020E88C(commit, 0x14);
}

u16 fn_8020EE24(s32 chan)
{
    OSSramEx *sram = LockSramEx();
    u16 id = sram->wirelessPadID[chan];

    UnlockSramEx(0);
    return id;
}
