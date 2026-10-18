/* CreateCallbackFat: CARD create callback once the FAT has been written; fills in
 * the new directory entry and starts the directory update. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef u64 OSTime;
typedef void (*CARDCallback)(s32 channel, s32 result);

typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
} DVDDiskID;

typedef struct CARDFileInfo {
    s32 chan;
    s32 fileNo;
    s32 offset;
    s32 length;
    u16 iBlock;
    u16 padding;
} CARDFileInfo;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 padding0;
    u8 bannerFormat;
    u8 fileName[32];
    u32 time;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u8 permission;
    u8 copyTimes;
    u16 startBlock;
    u16 length;
    u8 padding1[2];
    u32 commentAddr;
} CARDDir;

typedef struct CARDControl {
    u8 reserved00[0xBC];
    u16 freeNo;
    u16 startBlock;
    CARDFileInfo *fileInfo;
    u8 reservedC4[0xC];
    CARDCallback apiCallback;
    u8 reservedD4[0x38];
    DVDDiskID *diskID;
} CARDControl;

extern CARDControl __CARDBlock[];
extern void *memcpy(void *dst, const void *src, u32 n);
extern CARDDir *__CARDGetDirBlock(CARDControl *card);
extern s32 __CARDUpdateDir(s32 channel, CARDCallback callback);
extern s32 __CARDPutControlBlock(CARDControl *card, s32 result);
extern OSTime OSGetTime(void);
extern s64 fn_800F5ECC(s64 dividend, s64 divisor);

void CreateCallbackFat(s32 channel, s32 result)
{
    CARDControl *card = &__CARDBlock[channel];
    CARDDir *ent;
    CARDCallback callback;
    u32 ticksPerSecond;

    callback = card->apiCallback;
    card->apiCallback = 0;
    if (result < 0) {
        goto error;
    }

    ent = &__CARDGetDirBlock(card)[card->freeNo];
    memcpy(ent->gameName, card->diskID->gameName, sizeof(ent->gameName));
    memcpy(ent->company, card->diskID->company, sizeof(ent->company));
    ent->permission = 4;
    ent->copyTimes = 0;
    ent->startBlock = card->startBlock;
    ent->bannerFormat = 0;
    ent->iconAddr = 0xFFFFFFFF;
    ent->iconFormat = 0;
    ent->iconSpeed = 0;
    ent->commentAddr = 0xFFFFFFFF;
    ent->iconSpeed = (ent->iconSpeed & ~3) | 1;
    card->fileInfo->offset = 0;
    card->fileInfo->iBlock = ent->startBlock;
    ticksPerSecond = *(u32 *)0x800000F8 >> 2;
    ent->time = (u32)fn_800F5ECC((s64)OSGetTime(), (s64)ticksPerSecond);
    result = __CARDUpdateDir(channel, callback);
    if (result >= 0) {
        return;
    }

error:
    __CARDPutControlBlock(card, result);
    if (callback) {
        callback(channel, result);
    }
}
