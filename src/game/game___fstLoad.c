/* __fstLoad: load disc identification and publish the FST in low memory. */

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBufSize;
    u8 padding[22];
} DVDDiskID;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCallback)(s32 result, DVDCommandBlock* block);

typedef struct BootBlock2 {
    u32 bootFilePosition;
    u32 fstPosition;
    u32 fstLength;
    u32 fstMaxLength;
    void* fstAddress;
    u32 userPosition;
    u32 userLength;
} BootBlock2;

extern void* OSGetArenaHi(void);
extern void OSSetArenaHi(void*);
extern void OSReport(const char*, ...);
extern void DVDReset(void);
extern s32 DVDReadDiskID(DVDCommandBlock*, DVDDiskID*, DVDCallback);
extern s32 DVDGetDriveStatus(void);
extern void* memcpy(void*, const void*, unsigned long);
extern void cb_80216778(s32, DVDCommandBlock*);
extern u8 bb2Buf_80641A58[63];
extern DVDCommandBlock block_80641A98;
extern BootBlock2* bb2_8064DA54;
extern DVDDiskID* idTmp_8064DA58;
extern char lbl_802FE6A0[];
extern char lbl_8064C410[2];
extern char lbl_8064C414[4];
extern char lbl_8064C418[3];

void __fstLoad(void)
{
    /* DVD transfers require a 32-byte-aligned destination. */
    u8 idBuffer[sizeof(DVDDiskID) + 32];
    DVDDiskID* id;
    struct { char* text; } messages;

    messages.text = lbl_802FE6A0;

    OSGetArenaHi();
    idTmp_8064DA58 = (DVDDiskID*)(((u32)idBuffer + 31) & ~31);
    bb2_8064DA54 = (BootBlock2*)(((u32)bb2Buf_80641A58 + 31) & ~31);
    DVDReset();
    DVDReadDiskID(&block_80641A98, idTmp_8064DA58, cb_80216778);
    while (DVDGetDriveStatus() != 0) {
    }

    *(void**)0x80000038 = bb2_8064DA54->fstAddress;
    *(u32*)0x8000003C = bb2_8064DA54->fstMaxLength;
    id = (DVDDiskID*)0x80000000;
    memcpy(id, idTmp_8064DA58, sizeof(DVDDiskID));
    OSReport(lbl_8064C410);
    OSReport(messages.text, id->gameName[0], id->gameName[1], id->gameName[2], id->gameName[3]);
    OSReport(messages.text + 0x1C, id->company[0], id->company[1]);
    OSReport(messages.text + 0x34, id->diskNumber);
    OSReport(messages.text + 0x48, id->gameVersion);
    OSReport(messages.text + 0x5C, id->streaming == 0 ? lbl_8064C414 : lbl_8064C418);
    OSReport(lbl_8064C410);
    OSSetArenaHi(bb2_8064DA54->fstAddress);
}
