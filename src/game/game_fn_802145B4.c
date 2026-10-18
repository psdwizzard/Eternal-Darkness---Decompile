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
struct DVDCommandBlock {
    u8 pad[0x0C];
    s32 state;
    s32 currTransferSize;
    u8 pad14[0x10];
    DVDDiskID *id;
    void (*callback)(s32, DVDCommandBlock *);
};

typedef struct DVDBootBlock {
    u32 bootFilePosition;
    u32 FSTPosition;
    u32 FSTLength;
    u32 FSTMaxLength;
} DVDBootBlock;

extern DVDCommandBlock *executing_8064DA00;
extern OSBootInfo *bootInfo_8064DA08;
extern DVDDiskID tmpBuffer_80641960;
extern s32 NumInternalRetry;
extern void (*lbl_8064DA48)(DVDCommandBlock *);

extern void __DVDStoreErrorCode(u32);
extern void DVDReset(void);
extern void cbForStateError_80213C1C(s32);
extern void stateReadingFST(DVDCommandBlock *);
extern void cbForStateReadingFST(u32);
extern void cbForStateGettingError(u32);
extern BOOL DVDLowRead(void *, u32, u32, void (*)(u32));
extern void DVDLowRequestError(void (*)(u32));

void cbForStateCheckID2(u32 intType)
{
    if (intType == 0x10) {
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError_80213C1C(0);
        return;
    }

    if (intType & 1) {
        NumInternalRetry = 0;
        lbl_8064DA48 = stateReadingFST;
        DVDLowRead(bootInfo_8064DA08->FSTLocation,
                     (((DVDBootBlock *)&tmpBuffer_80641960)->FSTLength + 31) & ~31U,
                     ((DVDBootBlock *)&tmpBuffer_80641960)->FSTPosition, cbForStateReadingFST);
    } else {
        DVDLowRequestError(cbForStateGettingError);
    }
}
