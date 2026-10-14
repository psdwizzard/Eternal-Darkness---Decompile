typedef unsigned char u8;
typedef int s32;
typedef int BOOL;

extern BOOL fn_802070C4(s32 chan);

/* CARDProbe */
BOOL fn_802201FC(s32 chan)
{
    if (*(u8 *)0x800030E3 & 0x80) {
        return 0;
    }
    return fn_802070C4(chan);
}
