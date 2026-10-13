typedef int BOOL;
typedef int s32;
typedef unsigned int u32;

extern BOOL EXISelect(s32 chan, u32 dev, u32 freq);
extern BOOL EXIImm(s32 chan, void *buf, s32 len, u32 type, void *callback);
extern BOOL EXISync(s32 chan);
extern BOOL EXIDeselect(s32 chan);

s32 fn_8021C6C8(s32 chan, BOOL enable)
{
    BOOL err;
    u32 cmd;

    if (!EXISelect(chan, 0, 4)) {
        return -3;
    }
    cmd = enable ? 0x81010000 : 0x81000000;
    err = !EXIImm(chan, &cmd, 2, 1, 0);
    err |= !EXISync(chan);
    err |= !EXIDeselect(chan);
    if (err) {
        return -3;
    }
    return 0;
}
