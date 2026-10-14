/* Initialize the DVD filesystem table and its string table. */

typedef unsigned int u32;

typedef struct FSTEntry {
    u32 isDirAndStringOff;
    u32 parentOrPosition;
    u32 nextEntryOrLength;
} FSTEntry;

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    unsigned char diskNumber;
    unsigned char gameVersion;
    unsigned char streaming;
    unsigned char streamingBufSize;
    unsigned char padding[22];
} DVDDiskID;

typedef struct OSBootInfo {
    DVDDiskID DVDDiskID;
    u32 magic;
    u32 version;
    u32 memorySize;
    u32 consoleType;
    void *arenaLo;
    void *arenaHi;
    void *FSTLocation;
    u32 FSTMaxLength;
} OSBootInfo;

extern OSBootInfo *BootInfo_8064D9E0;
extern FSTEntry *FstStart_8064D9E4;
extern char *FstStringStart_8064D9E8;
extern u32 MaxEntryNum_8064D9EC;

void __DVDFSInit(void)
{
    BootInfo_8064D9E0 = (OSBootInfo *)0x80000000;
    FstStart_8064D9E4 = BootInfo_8064D9E0->FSTLocation;
    if (FstStart_8064D9E4 != 0) {
        MaxEntryNum_8064D9EC = FstStart_8064D9E4->nextEntryOrLength;
        FstStringStart_8064D9E8 = (char *)(FstStart_8064D9E4 + MaxEntryNum_8064D9EC);
    }
}
