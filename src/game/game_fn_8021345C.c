/* DVDClose: cancel any outstanding command for this file. */
typedef int s32;
typedef int BOOL;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct DVDFileInfo DVDFileInfo;

extern s32 fn_80215FAC(DVDCommandBlock *block);

BOOL fn_8021345C(DVDFileInfo *fileInfo)
{
    /* The command block is the first member of DVDFileInfo. */
    fn_80215FAC((DVDCommandBlock *)fileInfo);
    return 1;
}
