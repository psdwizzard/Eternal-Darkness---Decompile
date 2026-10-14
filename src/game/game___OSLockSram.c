typedef int BOOL;
typedef unsigned char u8;
typedef unsigned int u32;

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

void *__OSLockSram(void)
{
    SramControlBlock *scb = &Scb_80640E40;
    BOOL enabled = OSDisableInterrupts();
    BOOL *locked = &scb->locked;

    if (*locked) {
        OSRestoreInterrupts(enabled);
        scb = 0;
    } else {
        scb->enabled = enabled;
        *locked = 1;
    }
    return scb;
}
