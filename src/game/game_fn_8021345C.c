/* DVDClose: cancel any outstanding command for this file. */
typedef int s32;
typedef int BOOL;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct DVDFileInfo DVDFileInfo;

extern s32 DVDCancel(DVDCommandBlock *block);

BOOL DVDClose(DVDFileInfo *fileInfo)
{
    /* The command block is the first member of DVDFileInfo. */
    DVDCancel((DVDCommandBlock *)fileInfo);
    return 1;
}
