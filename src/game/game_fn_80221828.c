/* fn_80221828: CARDClose. */
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

extern s32 fn_8021D2BC(s32 chan, CARDControl **card);
extern s32 fn_8021D374(CARDControl *card, s32 result);

s32 fn_80221828(CARDFileInfo *fileInfo)
{
    CARDControl *card;
    s32 result;

    result = fn_8021D2BC(fileInfo->chan, &card);
    if (result < 0) {
        return result;
    }

    fileInfo->chan = -1;
    return fn_8021D374(card, 0);
}
