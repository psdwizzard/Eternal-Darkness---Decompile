/* fn_8021EF3C: __CARDGetDirBlock (Dolphin SDK CARDDir.c). */

typedef struct CARDDir CARDDir;

typedef struct CARDControl {
    unsigned char reserved00[0x80];
    void *workArea;
    CARDDir *currentDir;
} CARDControl;

CARDDir *fn_8021EF3C(CARDControl *card)
{
    return card->currentDir;
}
