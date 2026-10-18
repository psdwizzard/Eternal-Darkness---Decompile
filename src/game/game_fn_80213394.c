/* DVDOpen (0x80213394, 200 bytes): DVDOpen (SDK dvdfs.c) */

typedef int s32;
typedef unsigned int u32;
typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct FSTEntry {
    unsigned int isDirAndStringOff;
    unsigned int parentOrPosition;
    unsigned int nextEntryOrLength;
} FSTEntry;

typedef struct DVDFileInfo {
    char unk0[0xC];
    s32 state; /* cb.state */
    char unk10[0x20];
    u32 startAddr;
    u32 length;
    void *callback;
} DVDFileInfo;

extern s32 DVDConvertPathToEntrynum(char *pathPtr); /* DVDConvertPathToEntrynum */
extern BOOL DVDGetCurrentDir(char *path, u32 maxlen); /* DVDGetCurrentDir */
extern void OSReport(const char *msg, ...);

extern FSTEntry *FstStart_8064D9E4;
extern char lbl_802FE218[]; /* "Warning: DVDOpen(): file '%s' was not found under %s.\n" */

#define entryIsDir(i) (((FstStart_8064D9E4[i].isDirAndStringOff & 0xff000000) == 0) ? FALSE : TRUE)
#define filePosition(i) (FstStart_8064D9E4[i].parentOrPosition)
#define fileLength(i) (FstStart_8064D9E4[i].nextEntryOrLength)

BOOL DVDOpen(char *fileName, DVDFileInfo *fileInfo) {
    s32 entry;
    char currentDir[128];

    entry = DVDConvertPathToEntrynum(fileName);

    if (0 > entry) {
        DVDGetCurrentDir(currentDir, 128);
        OSReport(lbl_802FE218, fileName, currentDir);
        return FALSE;
    }

    if (entryIsDir(entry)) {
        return FALSE;
    }

    fileInfo->startAddr = filePosition(entry);
    fileInfo->length = fileLength(entry);
    fileInfo->callback = (void *)0;
    fileInfo->state = 0;

    return TRUE;
}
