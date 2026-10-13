/* fn_8020E88C: UnlockSram (OSRtc), with WriteSram inlined. */

typedef int BOOL;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef signed char s8;
typedef unsigned char u8;

typedef void (*EXICallback)(s32 chan, void *context);

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

#define SRAM ((OSSram *)Scb_80640E40.sram)

extern void OSRestoreInterrupts(BOOL enabled);
extern BOOL EXILock(s32 chan, u32 dev, EXICallback callback);
extern BOOL EXIUnlock(s32 chan);
extern BOOL EXISelect(s32 chan, u32 dev, u32 freq);
extern BOOL EXIImm(s32 chan, void *buf, s32 len, u32 type, void *callback);
extern BOOL EXISync(s32 chan);
extern BOOL EXIDeselect(s32 chan);
extern BOOL fn_80206AC8(s32 chan, void *buf, s32 len, u32 type);
extern void fn_8020E528(s32 chan, void *context);

static inline BOOL WriteSram(void *buffer, u32 offset, u32 size)
{
    BOOL err;
    u32 cmd;

    if (!EXILock(0, 1, fn_8020E528)) {
        return 0;
    }
    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return 0;
    }

    offset <<= 6;
    cmd = 0xA0000000 | 0x100 + offset;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !fn_80206AC8(0, buffer, (s32)size, 1);
    err |= !EXIDeselect(0);
    EXIUnlock(0);

    return !err;
}

BOOL fn_8020E88C(BOOL commit, u32 offset)
{
    SramControlBlock *scb = &Scb_80640E40;
    u32 *cur;
    u16 *p;

    if (commit) {
        if (offset == 0) {
            OSSram *sram = (OSSram *)scb->sram;

            if (2u < (sram->flags & 3)) {
                sram->flags &= ~3;
            }

            sram->checkSum = sram->checkSumInv = 0;
            for (p = (u16 *)&sram->counterBias; p < (u16 *)(scb->sram + sizeof(OSSram)); p++) {
                sram->checkSum += *p;
                sram->checkSumInv += ~*p;
            }
        }

        if (offset < *(cur = &scb->offset)) {
            *cur = offset;
        }

        scb->sync = WriteSram(scb->sram + *cur, *cur, 64 - *cur);
        if (scb->sync) {
            *cur = 64;
        }
    }
    scb->locked = 0;
    OSRestoreInterrupts(scb->enabled);
    return scb->sync;
}
