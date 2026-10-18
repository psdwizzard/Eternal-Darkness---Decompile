typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef int BOOL;

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
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

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDLowCallback)(u32 intType);

typedef struct DVDBootBlock {
    u32 bootFilePosition;
    u32 FSTPosition;
    u32 FSTLength;
    u32 FSTMaxLength;
} DVDBootBlock;

extern OSBootInfo *bootInfo_8064DA08;
extern DVDDiskID tmpBuffer_80641960;
extern void (*lbl_8064DA48)(DVDCommandBlock *);

extern void cbForStateReadingFST(u32 intType);
extern BOOL DVDLowRead(void *addr, u32 length, u32 offset,
                        DVDLowCallback callback);

/* Read the file system table, retaining this state for drive-error retries. */
void stateReadingFST(DVDCommandBlock *block)
{
    lbl_8064DA48 = stateReadingFST;
    DVDLowRead(bootInfo_8064DA08->FSTLocation,
                 (((DVDBootBlock *)&tmpBuffer_80641960)->FSTLength + 31) & ~31U,
                 ((DVDBootBlock *)&tmpBuffer_80641960)->FSTPosition,
                 cbForStateReadingFST);
}
