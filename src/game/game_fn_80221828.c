/* CARDClose: CARDClose. */
typedef signed int s32;
typedef unsigned short u16;

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
    u16 padding;
} CARDFileInfo;

typedef struct CARDControl CARDControl;

extern s32 __CARDGetControlBlock(s32 chan, CARDControl **card);
extern s32 __CARDPutControlBlock(CARDControl *card, s32 result);

s32 CARDClose(CARDFileInfo *fileInfo)
{
    CARDControl *card;
    s32 result;

    result = __CARDGetControlBlock(fileInfo->chan, &card);
    if (result < 0) {
        return result;
    }

    fileInfo->chan = -1;
    return __CARDPutControlBlock(card, 0);
}
