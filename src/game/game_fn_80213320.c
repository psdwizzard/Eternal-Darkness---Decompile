/* DVDFastOpen: open a file by its filesystem table entry number. */

typedef int s32;
typedef unsigned int u32;
typedef int BOOL;

typedef struct FSTEntry {
    u32 isDirAndStringOff;
    u32 parentOrPosition;
    u32 nextEntryOrLength;
} FSTEntry;

typedef struct DVDFileInfo {
    char unk0[0xC];
    s32 state;
    char unk10[0x20];
    u32 startAddr;
    u32 length;
    void *callback;
} DVDFileInfo;

extern FSTEntry *FstStart_8064D9E4;
extern u32 MaxEntryNum_8064D9EC;

#define entryIsDir(i) (((FstStart_8064D9E4[i].isDirAndStringOff & 0xff000000) == 0) ? 0 : 1)

BOOL DVDFastOpen(s32 entry, DVDFileInfo *fileInfo) {
    if (entry < 0 || entry >= MaxEntryNum_8064D9EC || entryIsDir(entry)) {
        return 0;
    }

    fileInfo->startAddr = FstStart_8064D9E4[entry].parentOrPosition;
    fileInfo->length = FstStart_8064D9E4[entry].nextEntryOrLength;
    fileInfo->callback = (void *)0;
    fileInfo->state = 0;
    return 1;
}
