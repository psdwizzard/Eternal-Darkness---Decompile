/* fn_8020E588: WriteSram (OSRtc). */

typedef int BOOL;
typedef int s32;
typedef unsigned int u32;

typedef void (*EXICallback)(s32 chan, void *context);

extern BOOL EXILock(s32 chan, u32 dev, EXICallback callback);
extern BOOL EXIUnlock(s32 chan);
extern BOOL EXISelect(s32 chan, u32 dev, u32 freq);
extern BOOL EXIImm(s32 chan, void *buf, s32 len, u32 type, void *callback);
extern BOOL EXISync(s32 chan);
extern BOOL EXIDeselect(s32 chan);
extern BOOL fn_80206AC8(s32 chan, void *buf, s32 len, u32 type);
extern void fn_8020E528(s32 chan, void *context);

BOOL fn_8020E588(void *buffer, u32 offset, u32 size)
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
