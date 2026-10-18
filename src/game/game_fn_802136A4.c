/* DVDChangeDir: select a directory by its filesystem path. */

typedef int s32;
typedef unsigned int u32;
typedef int BOOL;

typedef struct FSTEntry {
    u32 isDirAndStringOff;
    u32 parentOrPosition;
    u32 nextEntryOrLength;
} FSTEntry;

extern s32 DVDConvertPathToEntrynum(char *pathPtr); /* DVDConvertPathToEntrynum */
extern FSTEntry *FstStart_8064D9E4;
extern u32 currentDirectory; /* currentDirectory */

#define entryIsDir(i) (((FstStart_8064D9E4[i].isDirAndStringOff & 0xff000000) == 0) ? 0 : 1)

BOOL DVDChangeDir(char *path)
{
    s32 entry = DVDConvertPathToEntrynum(path);

    if (entry < 0 || !entryIsDir(entry)) {
        return 0;
    }

    currentDirectory = entry;
    return 1;
}
