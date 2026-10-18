typedef unsigned char u8;
typedef int s32;
typedef int BOOL;

extern BOOL EXIProbe(s32 chan);

/* CARDProbe */
BOOL CARDProbe(s32 chan)
{
    if (*(u8 *)0x800030E3 & 0x80) {
        return 0;
    }
    return EXIProbe(chan);
}
