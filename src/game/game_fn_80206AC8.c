typedef int BOOL;
typedef int s32;
typedef unsigned char u8;
typedef unsigned int u32;

extern BOOL EXIImm(s32 chan, void *buf, s32 len, u32 type, void *callback);
extern BOOL EXISync(s32 chan);

BOOL fn_80206AC8(s32 chan, void *buf, s32 len, u32 type)
{
    s32 xLen;

    while (len != 0) {
        xLen = len < 4 ? len : 4;
        if (!EXIImm(chan, buf, xLen, type, 0)) {
            return 0;
        }
        if (!EXISync(chan)) {
            return 0;
        }
        buf = (u8 *)buf + xLen;
        len -= xLen;
    }
    return 1;
}
