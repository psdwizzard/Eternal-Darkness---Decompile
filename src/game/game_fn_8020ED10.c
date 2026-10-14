/* Read the progressive display mode bit from SRAM. */
typedef int BOOL;
typedef unsigned int u32;
typedef unsigned short u16;
typedef signed char s8;
typedef unsigned char u8;

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
extern void OSRestoreInterrupts(BOOL enabled);
extern BOOL fn_8020E88C(BOOL commit, u32 offset);

static inline OSSram *LockSram(u32 offset)
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
    return (OSSram *)(scb->sram + offset);
}

static inline OSSram *LockBaseSram(void)
{
    return LockSram(0);
}

u32 fn_8020ED10(void)
{
    OSSram *sram = LockBaseSram();
    u32 mode = (sram->flags >> 7) & 1;

    fn_8020E88C(0, 0);
    return mode;
}
