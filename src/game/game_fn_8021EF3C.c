/* __CARDGetDirBlock: __CARDGetDirBlock (Dolphin SDK CARDDir.c). */

typedef struct CARDDir CARDDir;

typedef struct CARDControl {
    unsigned char reserved00[0x80];
    void *workArea;
    CARDDir *currentDir;
} CARDControl;

CARDDir *__CARDGetDirBlock(CARDControl *card)
{
    return card->currentDir;
}
