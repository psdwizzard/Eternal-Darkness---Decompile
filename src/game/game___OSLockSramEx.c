typedef int BOOL;
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSSram {
    u16 checkSum;
    u16 checkSumInv;
    u32 ead0;
    u32 ead1;
    u32 counterBias;
    s8 displayOffsetH;
    u8 ntd;
    u8 language;
    u8 flags;
} OSSram;

typedef struct SramControlBlock {
    u8 sram[64];
    u32 offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
    void (*callback)(void);
} SramControlBlock;

extern SramControlBlock Scb_80640E40;
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);

static void *LockSram(u32 offset)
{
    u8 *sram = Scb_80640E40.sram;
    BOOL enabled = OSDisableInterrupts();

    if (Scb_80640E40.locked) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    Scb_80640E40.enabled = enabled;
    Scb_80640E40.locked = 1;
    return sram + offset;
}

void *__OSLockSramEx(void)
{
    return LockSram(sizeof(OSSram));
}
