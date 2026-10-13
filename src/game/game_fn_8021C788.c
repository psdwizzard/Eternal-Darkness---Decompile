typedef int BOOL;
typedef int s32;
typedef unsigned int u32;

extern BOOL EXISelect(s32 chan, u32 dev, u32 freq);
extern BOOL EXIImm(s32 chan, void *buf, s32 len, u32 type, void *callback);
extern BOOL EXISync(s32 chan);
extern BOOL EXIDeselect(s32 chan);

s32 fn_8021C788(s32 chan, void *buf)
{
    BOOL err;
    u32 cmd;

    if (!EXISelect(chan, 0, 4)) {
        return -3;
    }
    cmd = 0x83000000;
    err = !EXIImm(chan, &cmd, 2, 1, 0);
    err |= !EXISync(chan);
    err |= !EXIImm(chan, buf, 1, 0, 0);
    err |= !EXISync(chan);
    err |= !EXIDeselect(chan);
    if (err) {
        return -3;
    }
    return 0;
}
